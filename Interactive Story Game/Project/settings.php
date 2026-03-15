<?php
include 'inc/navbar.php';
    ?>
   <div class="set">
    <h1>Settings</h1>
    <audio id="ms" src="sound/ofeliasdream.mp3" autoplay loop></audio>
    <div>
     <label for="volume">Volume</label>
  <input type="range" id="volume" name="volume"
         min="0" max="100">
 
</div>
   
   <script>
       
    let vol=document.getElementById('volume');
    let music=document.getElementById("ms");
       document.cookie="volume="+parseFloat((vol.value/100))+";";
       function setvol(){
             music.volume=parseFloat((vol.value/100));
           document.cookie="volume="+parseFloat((vol.value/100))+";";
       }
      
        vol.addEventListener('click',setvol);
     
    </script>
    
   
    
  
    

 <div class="bottom">
		<div class="container">
		
		<div class="d-flex justify-content-center" >
			<p>Copyright B&D <?php echo date('Y') ?> </p>
            </div>
		</div>
            
    </div>
    </body>
    
    </html>