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
   <div class="how">
    <h1>How to play</h1>
    <p>This is a "Make your own story" game: </p><br>
    <p>You get to be the God of your own Universe. Going forwards in the story will be done by clicking on the arrow which will give you a list of choices. After careful consideration, you should click on the CHOOSE button and your story will continue.</p><br>
       <p id="animation" style="font-size:45px">PAY ATTENTION!</p><p>Every choice will affect your story!</p>
    <script>
        let state = true;
        function red() {
			document.getElementById("animation").style.color="red";
		}

		function yellow() {
			document.getElementById("animation").style.color="yellow";
		}
        function auto(){
            if(state===true){
                red();
                state=false;
            }
            else{
                yellow();
                state=true;
            }
           
        }
        let autolight =setInterval(auto,1000);
    </script> 
    
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