<html>
<head>
    <title> a4.php </title>
</head>
<!--Style elements that style the webpage-->
<body>
<style>
    .filesOutline
    {
        border: 1px solid black;
        width: 350px;
        padding: 5px;
    }

    .popUpBackground
    {
        background-color: #FFFFFF;
        padding: 25px 85px 25px;
    }

    .popUpDisplay
    {
        display: none;
        position: absolute;
        left: 250px;
        z-index: 1001;
        top: 100;
    }

    .dimBackground
    {
        display: none;
        height: 100%;
        width: 100%;
        background: #A9A9A9;
        top: 0px;
        position: absolute;
        opacity: 0.5;
    }
</style>
<body>
    <!--Convert button-->
    <input type="button" name="buttonchoice" id="clickMe" value="Convert" onclick="javascript:openPopUp()" />
    <input type="button" name="buttonchoice2" id="clickMe2" value="DB Store" onclick="javascript:openPopUp2()" />
    <!--Upload button-->
    <form action="upload.php" method="post" enctype="multipart/form-data">
        <input type="file" name="fileToUpload" id="fileToUpload" >
        <input type="submit" value="Upload" name="submit">
    </form>

    <!-- Javascript functions that open and close the popup window -->
    <script type="text/javascript">
        var element;
        <!-- Opens popup when convert is pressed, disables background layer-->
        function openPopUp()
        {
            element = document.getElementById("background");
            element.style.display = "block";
            element = document.getElementById("popup");
            element.style.display = "block";
        }
        <!-- Closes popup when cancel is pressed, enables background layer-->
        function closePopUp()
        {
            element = document.getElementById("popup");
            element.style.display = "none";
            element = document.getElementById("background");
            element.style.display = "none";
        }
        function openPopUp2()
        {
            element = document.getElementById("background2");
            element.style.display = "block";
            element = document.getElementById("popup2");
            element.style.display = "block";
        }
        function closePopUp2()
        {
            element = document.getElementById("popup2");
            element.style.display = "none";
            element = document.getElementById("background2");
            element.style.display = "none";
        }
    </script>

<!--Makes borders around the files on the main page, and prints files to screen -->
<div class="filesOutline">
<?php
    //Open the files directory
    $dir = "./files";
    if ($dirHandle = opendir($dir))
    {
        //While we are not done reading the files in the directory, keep going
        while(($file = readdir($dirHandle)) != false)
        {
            $file_parts = pathinfo($file);
            if ($file != "." && $file != "..")
            {
                switch($file_parts['extension'])
                {
                    //If this is a txt file, print it out and add it to an array
                    case "txt":
                    echo "<a href='./files/$file'>$file</a><BR>";
                    $txtArray[] =  $file;
                    break;
                }
            }
        }
        closedir($dirHandle);
    }
    echo '</div>';
    echo '<BR>';
    echo '<div class="filesOutline">';

    //Second box that shows .html files
    $dir = "./files";
    if ($dirHandle = opendir($dir))
    {
        while(($file = readdir($dirHandle)) != false)
        {
            $file_parts = pathinfo($file);
            switch($file_parts['extension'])
            {
                //If this is a .html file, add it to the array
                case "html":
                $htmlFiles[]= $file;
                break;
            }
        }
        //Sort html files alphabetically
        natsort($htmlFiles);
        foreach($htmlFiles as $file)
        {
            echo("<a href='./files/$file'>$file</a><BR>");
        }
        closedir($dirHandle);
    }
    echo '</div>';


    //Call the dimming layer, without this we can't have popups
    echo '<div id="background" class="dimBackground"></div>';
    //Puts popup in box as expected for look
    echo '<div id="popup" class="popUpDisplay">';
    //Puts whitebox around popup box
    echo '<div class="popUpBackground">';
    //Creates the form that our selection box is in, recalls the a4.php page
    echo '<form action="a4.php">';
    echo '<select name="selectedFile" size="8">';
    //For each file in the txt array, display it in the selection box
    foreach ($txtArray as $value)
    {
        echo '<option value="';echo $value;echo'">';echo $value;'</option>';
    }
    echo '</select>';
    echo ' <br><br>';
    //Cancel button for selection menu
    echo '<input id="clickMe" type="button" value="Cancel" onclick="closePopUp()" />';
    //Ok button for selection menu
    echo '<input type="submit" value= "OK">';
    echo '</form>';
    echo '</div>';
    echo ' </div>';

    //Get the file that was selected and save it
    $selectedFile =  $_GET['selectedFile'];

    //If a file has been selected, convert it
    if(!empty($selectedFile))
    {
        //Sending convert command to terminal
        $command = "./a4 files/" . $selectedFile . " -c";
        //Execute C code with the selected file from the GUI
        exec($command . " > /dev/null &");
    }


    // THIS is the seocond pop up window
     //Call the dimming layer, without this we can't have popups
    echo '<div id="background2" class="dimBackground"></div>';
    //Puts popup in box as expected for look
   echo '<div id="popup2" class="popUpDisplay">';
    //Puts whitebox around popup box
    echo '<div class="popUpBackground">';
    //Creates the form that our selection box is in, recalls the a4.php page
    echo '<form action="a4.php">';
    echo '<select name="selectedFile2" size="8">';
    //For each file in the txt array, display it in the selection box
    foreach ($txtArray as $value)
    {
        echo '<option value="';echo $value;echo'">';echo $value;'</option>';
    }
    echo '</select>';
    echo ' <br><br>';
    //Cancel button for selection menu
    echo '<input id="clickMe2" type="button" value="Cancel" onclick="closePopUp2()" />';
    //Ok button for selection menu
    echo '<input type="submit" value= "OK">';
    echo '</form>';
    echo '</div>';
    echo ' </div>';

    //Get the file that was selected and save it
    $selectedFile2 =  $_GET['selectedFile2'];

    //If a file has been selected, convert it
    if(!empty($selectedFile2))
    {
        //Sending convert command to terminal
        $command = "./a4 files/" . $selectedFile2 . " -db";
        //Execute C code with the selected file from the GUI
        exec($command . " > /dev/null &");
    }


    echo'</body></html>';
?>
