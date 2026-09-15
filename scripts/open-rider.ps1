param(
  [Parameter(Mandatory=$true)][string]$ProjectDirectory,
  [Parameter(Mandatory=$true)][string]$SourceFile,
  [string]$SessionFile,
  [switch]$CheckOnly,
  [switch]$RegisterOnly
)
$ErrorActionPreference = 'Stop'
$projectPath = (Resolve-Path -LiteralPath $ProjectDirectory).Path
$sourcePath = (Resolve-Path -LiteralPath $SourceFile).Path
if (-not $sourcePath.StartsWith($projectPath + '\', [StringComparison]::OrdinalIgnoreCase)) {
  throw 'Source file must be inside the project directory.'
}
if (-not $CheckOnly) {
  $sources = @($sourcePath)
  if ($SessionFile) {
    $session = Get-Content -LiteralPath $SessionFile -Raw -Encoding UTF8 | ConvertFrom-Json
    if ([IO.Path]::GetFullPath($session.project) -ne $projectPath) { throw 'Session project mismatch.' }
    $sources = @($session.entries | ForEach-Object {
      $item = Get-Item -LiteralPath (Join-Path $projectPath $_.localFile)
      if (($item.Attributes -band [IO.FileAttributes]::ReparsePoint) -or
          -not $item.FullName.StartsWith($projectPath + '\', [StringComparison]::OrdinalIgnoreCase) -or $item.Extension -ne '.cpp') {
        throw 'Invalid project source path.'
      }
      $item.FullName
    })
  }
  $projects = @(Get-ChildItem -LiteralPath $projectPath -Filter '*.vcxproj' -File)
  if ($projects.Count -ne 1) { throw 'Expected exactly one .vcxproj in the Rider project folder.' }
  $vcxPath = $projects[0].FullName
  $ns = 'http://schemas.microsoft.com/developer/msbuild/2003'
  $xml = New-Object System.Xml.XmlDocument
  $xml.PreserveWhitespace = $true
  $xml.Load($vcxPath)
  $filtersPath = $vcxPath + '.filters'
  $filters = New-Object System.Xml.XmlDocument
  $filters.PreserveWhitespace = $true
  if (Test-Path -LiteralPath $filtersPath) { $filters.Load($filtersPath) }
  else { $filters.LoadXml('<?xml version="1.0" encoding="utf-8"?><Project xmlns="http://schemas.microsoft.com/developer/msbuild/2003" />') }
  $changed = $false
  $filtersChanged = $false
  foreach ($source in $sources) {
    $relative = $source.Substring($projectPath.Length + 1)
    $item = @($xml.SelectNodes('//*[local-name()="ItemGroup"]/*[@Include]') | Where-Object {
      $_.GetAttribute('Include').Replace('/', '\') -eq $relative
    })
    if ($item.Count -eq 0) {
      $group = $xml.CreateElement('ItemGroup', $ns)
      $entry = $xml.CreateElement('ClCompile', $ns)
      $entry.SetAttribute('Include', $relative)
      # Add a C++ project item without linking all independent main() functions together.
      $excluded = $xml.CreateElement('ExcludedFromBuild', $ns)
      $excluded.InnerText = 'true'
      [void]$entry.AppendChild($excluded)
      [void]$group.AppendChild($entry)
      [void]$xml.DocumentElement.AppendChild($group)
      $item = @($entry)
      $changed = $true
    }
    $filterItem = @($filters.SelectNodes('//*[local-name()="ItemGroup"]/*[@Include]') | Where-Object {
      $_.GetAttribute('Include').Replace('/', '\') -eq $relative
    })
    if ($filterItem.Count -eq 0) {
      $group = $filters.CreateElement('ItemGroup', $ns)
      $entry = $filters.CreateElement($item[0].LocalName, $ns)
      $entry.SetAttribute('Include', $relative)
      [void]$group.AppendChild($entry)
      [void]$filters.DocumentElement.AppendChild($group)
      $filtersChanged = $true
    }
  }
  if ($changed -or $filtersChanged) {
    $backupDir = Join-Path $projectPath ('.psf-project-backups\' + [Guid]::NewGuid().ToString())
    [void](New-Item -ItemType Directory -Path $backupDir -Force)
    if ($changed) {
      Copy-Item -LiteralPath $vcxPath -Destination $backupDir
      $xml.Save($vcxPath)
    }
    if ($filtersChanged) {
      if (Test-Path -LiteralPath $filtersPath) { Copy-Item -LiteralPath $filtersPath -Destination $backupDir }
      $filters.Save($filtersPath)
    }
  }
  Write-Output "Project items ready: $($sources.Count)"
  if ($RegisterOnly) { exit 0 }
}
$riderPath = $env:PSF_RIDER
if (-not $riderPath) {
  $command = Get-Command rider64.exe -ErrorAction SilentlyContinue
  if ($command) { $riderPath = $command.Source }
}
if (-not $riderPath) {
  $jetbrains = Join-Path $env:ProgramFiles 'JetBrains'
  $riderPath = Get-ChildItem -LiteralPath $jetbrains -Directory -ErrorAction SilentlyContinue |
    Where-Object { $_.Name -like '*Rider*' } |
    Sort-Object LastWriteTime -Descending |
    ForEach-Object { Join-Path $_.FullName 'bin\rider64.exe' } |
    Where-Object { Test-Path -LiteralPath $_ -PathType Leaf } |
    Select-Object -First 1
}
if (-not $riderPath -or -not (Test-Path -LiteralPath $riderPath -PathType Leaf)) {
  throw 'Rider not found. Set PSF_RIDER to the full path of rider64.exe.'
}
$solution = Get-ChildItem -LiteralPath $projectPath -File |
  Where-Object { $_.Extension -in '.slnx', '.sln' } |
  Sort-Object Name | Select-Object -First 1
$openPath = if ($solution) { $solution.FullName } else { $projectPath }
if ($CheckOnly) {
  Write-Output "Rider: $riderPath"
  Write-Output "Project: $openPath"
  Write-Output "File: $sourcePath"
  exit 0
}
# Open the solution first, then focus its source file using Rider's documented CLI.
Start-Process -FilePath $riderPath -ArgumentList @('"' + $openPath + '"') -WindowStyle Normal
Start-Sleep -Milliseconds 1000
Start-Process -FilePath $riderPath -ArgumentList ('--line 1 "' + $sourcePath + '"') -WindowStyle Normal
