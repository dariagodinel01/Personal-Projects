<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <link rel="stylesheet" type="text/css" href="css/style.css">
    <link rel="stylesheet" href="css/bootstrap.css">
    <title>Make Your Story</title>
</head>
<body>



<div class="top">
<div class="container">
<div class="d-flex flex-row-reverse">

<div class="navigation">
<ul>
    <li><a href="index.php">Home</a></li>
    <?php
    session_start();
 
    if(isset($_SESSION["logged_in"])){
        if($_SESSION["logged_in"]==true){
            $text="<li><a href='logout.php'>Hello ";
        $text.=$_SESSION['user'];
        $text.="</a></li>";
            echo $text;
        }
          else
        echo"<li><a href='login.php'>Log in </a></li>
    <li><a href='signin.php'>Sign up </a></li>";
         
        
    }
     else
        echo"<li><a href='login.php'>Log in </a></li>
    <li><a href='signin.php'>Sign up </a></li>";
    
    ?>
    
</ul>
    </div>
    
</div>
    </div>
    </div>
