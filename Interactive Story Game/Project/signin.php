<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Signin</title>
    <link rel="stylesheet" type="text/css" href="css/stylelog.css">
    <link rel="stylesheet" href="css/bootstrap.css">
</head>
<body>
    <div class="login">
    <a href="index.php">
        <img src="images/x.png" alt="" style="height:25px;width:auto;left:335px;position: absolute">
    </a>
    <h1>CREATE ACCOUNT</h1>
    <form action="" method="POST">
        Username
        <input type="text" name="user" placeholder="Insert Username">
        Password
        <input type="password" name="password" placeholder="Insert Password">
        Confirm Password
        <input type="password" name="password2" placeholder="Insert Password">
        <input type="submit" name="submit" value="REGISTER NOW">
        <a href="login.php">Already have an account? Log in now</a><br>
    </form>

<?php
        session_start();
    if(isset($_POST['submit'])){
        $username = $_POST['user'];
        $password = $_POST['password'];
        $password2 = $_POST['password2'];
        $sql = "SELECT * FROM users";
        $conn = mysqli_connect('localhost', 'root', 'admin') or die(mysqli_error());
        $db_select = mysqli_select_db($conn, 'game') or die(mysqli_error());
        $res = mysqli_query($conn, $sql);
        if($res==TRUE){
            $count=mysqli_num_rows($res);
            $ok=true;
            if($count>0){
                while($rows=mysqli_fetch_assoc($res)){
                    $usernamedb=$rows['Username'];
                   if($username==$usernamedb){
                       $ok=false;
                   }
                    
                      }
            }
        }

                    
        if($ok==true){
            
              if(strlen($password)<5){
             echo "<p>The password should have at least 5 characters</p>";
        }
        else{
            if($password!=$password2){
            echo "<p>The passwords do not match</p>";
        }
        else{
             $_SESSION['user']=$username;
        $sql = "INSERT INTO users SET
        Username = '$username',
        Password = '$password'
        ";
        
        $conn = mysqli_connect('localhost', 'root', 'admin') or die(mysqli_error());
        $db_select = mysqli_select_db($conn, 'game') or die(mysqli_error());
        $res = mysqli_query($conn, $sql) or die(mysqli_error());
        
        if($res == TRUE){
             $_SESSION["logged_in"] = true; 
            header("Location: http://localhost/projectIWP/index.php");
            die();
        }
        }
        }
        }
        else{
            echo "<p>The username already exists</p>";
        }
      
        
        
        
       
    }
?>
    </div>
</body>
</html>