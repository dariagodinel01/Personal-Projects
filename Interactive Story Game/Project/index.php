<?php
include 'inc/navbar.php';
    ?>
     <audio id="ms" src="sound/ofeliasdream.mp3" autoplay loop></audio>
    <script>
        function readCookie(name) {
    var nameEQ = name + "=";
    var ca = document.cookie.split(';');
    for(var i=0;i < ca.length;i++) {
        var c = ca[i];
        while (c.charAt(0)==' ') c = c.substring(1,c.length);
        if (c.indexOf(nameEQ) == 0) return c.substring(nameEQ.length,c.length);
    }
    return null;
}
        let music=document.getElementById('ms');
        let vol=readCookie('volume');
         music.volume=vol;
</script>

<div class="menu">
  <div class="container">
  <div class=" d-flex justify-content-center flex-direction: column">
   <div class="col-md-12">
    <h1>MENU</h1>
    <ul>
        <li><a href="play.php">PLAY</a></li>
        <li><a href="settings.php">SETTINGS</a></li>
        <li><a href="how.php">HOW TO PLAY</a></li>
    </ul>
   
      </div>
      </div>
    
    </div>
</div>
		<div class="bottom">
		<div class="container">
		
		<div class="d-flex justify-content-center">
			<p>Copyright B&D <?php echo date('Y') ?> </p>
            </div>
		</div>
            
    </div>
	
    </body>
    </html>