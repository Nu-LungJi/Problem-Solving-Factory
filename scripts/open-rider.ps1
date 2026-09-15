param(
  [Parameter(Mandatory=$true)][string]$ProjectDirectory,
  [Parameter(Mandatory=$true)][string]$SourceFile,
  [switch]$CheckOnly
)
$ErrorActionPreference = 'Stop'
$projectPath = (Resolve-Path -LiteralPath $ProjectDirectory).Path
$sourcePath = (Resolve-Path -LiteralPath $SourceFile).Path
if (-not $sourcePath.StartsWith($projectPath + '\', [StringComparison]::OrdinalIgnoreCase)) {
  throw 'Source file must be inside the project directory.'
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
Start-Process -FilePath $riderPath -ArgumentList @('--line', '1', '"' + $sourcePath + '"') -WindowStyle Normal
