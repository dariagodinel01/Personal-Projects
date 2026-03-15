<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Signin</title>
    <link rel="stylesheet" type="text/css" href="css/stylelog.css">
    <link rel="stylesheet" href="css/bootstrap.css">
</head>
<body>
    <div class="login" style="height:200px">
    <a href="index.php">
        <img src="images/x.png" alt="" style="height:25px;width:auto;left:335px;position: absolute">
    </a>
    <h1>DO YOU WANT TO LOG OUT?</h1>
    <form action="" method="POST">
        <input type="submit" name="submit" value="LOG OUT">
    </form>

<?php
        session_start();
    if(isset($_POST['submit'])){
        $_SESSION["logged_in"] = false; 
         $_SESSION['user']=" ";
        header("Location: http://localhost/projectIWP/index.php");
    }
?>
    </div>
</body>
</html>