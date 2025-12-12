# PowerShell build script; run: powershell -ExecutionPolicy Bypass -File .\build.ps1
$src = "src/main.cpp"
$out = "ecommerce.exe"

if (Get-Command g++ -ErrorAction SilentlyContinue) {
    & g++ -std=c++17 -O2 -Wall $src -o $out
    if ($LASTEXITCODE -eq 0) {
        Write-Host "Build succeeded with g++ -> $out"
        exit 0
    } else {
        Write-Host "g++ build failed"
        exit 1
    }
} elseif (Get-Command cl -ErrorAction SilentlyContinue) {
    & cl /EHsc /Fo:build\ /Fe:$out $src
    if ($LASTEXITCODE -eq 0) {
        Write-Host "Build succeeded with cl -> $out"
        exit 0
    } else {
        Write-Host "cl build failed"
        exit 1
    }
} else {
    Write-Host "No supported compiler found (g++ or cl). Install MinGW/MSYS2 or use Visual Studio Developer Tools."
    exit 2
}
