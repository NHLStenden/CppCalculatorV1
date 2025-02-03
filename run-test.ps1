echo "Running tests"
$stopwatch = [System.Diagnostics.Stopwatch]::StartNew()
Start-Process -FilePath .\cmake-build-release\CppCalculator -RedirectStandardInput "test-input.txt" -RedirectStandardOutput "test-output.txt" -NoNewWindow -Wait
$stopwatch.Stop()
$stopwatch.Elapsed

echo "Comparing output"
cmd /c fc /L test-output.txt test-output-check.txt > diff.txt
