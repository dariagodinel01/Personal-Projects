<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Login</title>
    <link rel="stylesheet" type="text/css" href="css/stylelog.css">
    <link rel="stylesheet" href="css/bootstrap.css">
</head>
<body>
    <div class="login">
     <a href="index.php">
        <img src="images/x.png" alt="" style="height:25px;width:auto;left:335px;position: absolute">
    </a>
    <h1>LOG IN</h1>
    <form action="" method="POST">
        <p>Username</p>
        <input type="text" name="user" placeholder="Insert Username">
        <p>Password</p>
        <input type="password" name="password" placeholder="Insert Password">
        <input type="submit" name="submit" value="LOG IN">
        <a href="signin.php">Don't have an account? Sign up now!</a><br>
    </form>
    <?php
        session_start();
        $conn = mysqli_connect('localhost', 'root', 'admin') or die(mysqli_error());
        $db_select = mysqli_select_db($conn, 'game') or die(mysqli_error());
         if(isset($_POST['submit'])){
        $username = $_POST["user"]; 
        $password = $_POST["password"];


        $select1 = "SELECT password FROM users WHERE Username = '".$username."'";

        $result1=$conn->query($select1);
        $row1=$result1->fetch_assoc();

        $select2 = "SELECT username FROM users WHERE Password = '".$password."'";

        $result2=$conn->query($select2);
        $row2=$result2->fetch_assoc();

             if(null!=$row2 && null!=$row1){
                 if($username == $row2["username"] && $password == $row1["password"]) 
        { 
             $_SESSION["logged_in"] = true; 
            $_SESSION["user"] = $username; 
              header("Location: http://localhost/projectIWP/index.php");
            die();

        }
        else
        {
            echo"<p>The username and password do not match!</p>";
        }
             }
             else{
                 echo"<p>The username or password are incorrect!</p>";
             }
             
        
         }
                    ?>
</div>
    </body>
</html>