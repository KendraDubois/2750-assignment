<?php
//Php file that uploads a file to the sever

//Set directory we are working in
$dir = "./files/";
$target_file = $dir . basename($_FILES["fileToUpload"]["name"]);

// Check if file already exists, if it does we do not upload (my choice professor said we can decide what we do with duplicates)
if (file_exists($target_file))
{
    //If there is a duplicate exit and reload a3.php
    header("Location: a4.php");
    exit;
}
//If there are no duplicates, upload the file
if (move_uploaded_file($_FILES["fileToUpload"]["tmp_name"], $target_file))
{
   //Print statement for debugging, will not show to user
   echo "The file ". basename( $_FILES["fileToUpload"]["name"]). " has been uploaded.";
}
else
{
    //Print statement for debugging, will not show to user
    echo "Sorry, there was an error uploading your file.";
}
header("Location: a4.php");
exit;

?>
