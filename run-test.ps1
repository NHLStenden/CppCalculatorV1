echo "Running tests"
$stopwatch = [System.Diagnostics.Stopwatch]::StartNew()
Start-Process -FilePath .\cmake-build-release\CppCalculator -RedirectStandardInput "test-input.txt" -RedirectStandardOutput "test-output.txt" -NoNewWindow -Wait
$stopwatch.Stop()
$stopwatch.ElapsedMilliseconds

echo "Comparing output"
cmd /c fc /L test-output.txt test-output-check.txt > diff.txt
if ($?) {
    Write-Host "De bestanden zijn identiek."
    exit 0
} else {
    Write-Host "Er zijn verschillen gevonden!"
    exit 1
}