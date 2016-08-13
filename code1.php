<html>
<head>
<title>Displaying.. </title>
</head>
<style type="text/css">
body{
  background: #E6E6FA;
}
h2{
  color: red; 
}
h5{
  border:5px solid black;
  margin:relative;
}
#left{
  margin-left:85px;
  padding-left: 80px; 
  float: left;
}
#right{
  float:right;
  margin-left:170px;
  padding-right: 165px;
}
</style>
<body>
<h1><a href="code2.php"><center>Search Again!</a></h1>
<?php
 if(isset($_POST['thr']))
  { 
	// echo "You have searched for: ",$_POST['thr'];
    $word=$_POST['thr'];
    $ans=exec("sudo /var/www/code/a.out $word",$ret);
	echo "<br><br>";		
    $pic=$ret[0];
	echo "<br>";

	if($pic!="error- openCV Exception")
	{
    //echo "<img src='data/templates/$pic.jpeg' alt='error' height='200' width='300' />";
	$dir = "data/train_images/$pic/";
    $file_display = array('jpeg','jpg','png');

    if (file_exists($dir) == false) 
	 {
    echo 'Directory \'', $dir, '\' not found!';
     } 
	else 
	 {
    $dir_contents = scandir($dir);
    foreach ($dir_contents as $file) 
	  {
      $file_type = strtolower(end(explode('.', $file)));
      }
    }

	$item=array();
	foreach(glob("$dir*.*") as $filename)
	 {
    $item[]=$filename;
	 }
	$arrlength=count($item);
    echo "<h2><center><strong><u>You have searched for:</u></strong></h2>";
    for($x=0;$x<$arrlength;$x++) 
	{
    $side="right";
    if($x%2==0) 
     {
       $side="left";
     } 
   ?>
      <div id="<?php echo $side;?>">   
<? 
   echo "<h5><img src='$item[$x]' alt='Image Not Displayed' height='200' width='300'></h5>";    ?>
   <br>
   </div>
<? }

}	
	else
		echo "NO SEARCH RESULTS!";
	echo "<br><br><br>";
  }
echo "<br><br><br>";
?>
<br>
</body>
</html>
