//convert ppts which in this folder to pdfs
$ppts = Get-Childitem *.ppt
$PowerPointApp = New-Object -ComObject PowerPoint.Application
$ppts
$opt = [Microsoft.Office.Interop.PowerPoint.PpSaveAsFileType]::ppSaveAsPDF 
foreach($n in $ppts){
    $n.FullName
    $pdfPath= $n.FullName + '.pdf'
    $document = $PowerPointApp.Presentations.Open($n.FullName)
    $document.SaveAs($pdfPath, $opt)
    #$document.ExportAsFixedFormat($pdfPath)
    $document.Close()
}
$PowerPointApp.Quit()