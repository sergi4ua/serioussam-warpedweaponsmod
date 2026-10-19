<#
.SYNOPSIS
  Fetches the Serious Sam Classics Patch 1.9.4 sources into ThirdParty\ClassicsPatch.

.DESCRIPTION
  The Classics Patch projects (Sources\ClassicsPatch) include the patch's Core, API and
  XGizmo headers, which in turn include the Steamworks SDK headers that the patch keeps in
  its repository. Those aren't redistributed with Warped Weapons, so they are fetched from
  the patch's own repository instead: tag 1.9.4 of SamClassicPatch/SuperProject plus its
  API and Extras/XGizmo submodules. Needs git.
#>
param()

$ErrorActionPreference = 'Stop'
$repo   = Split-Path -Parent $PSScriptRoot
$target = Join-Path $repo 'ThirdParty\ClassicsPatch'

if (Test-Path (Join-Path $target 'Core\Core.h')) {
  Write-Host "$target is already there."
  return
}
if (-not (Get-Command git -ErrorAction SilentlyContinue)) { throw 'git is required (https://git-scm.com/).' }

git clone --depth 1 --branch 1.9.4 https://github.com/SamClassicPatch/SuperProject.git $target
if ($LASTEXITCODE -ne 0) { throw "git clone failed ($LASTEXITCODE)" }
git -C $target submodule update --init --depth 1 API Extras/XGizmo
if ($LASTEXITCODE -ne 0) { throw "git submodule update failed ($LASTEXITCODE)" }
Write-Host "Serious Sam Classics Patch 1.9.4 sources are in $target"
