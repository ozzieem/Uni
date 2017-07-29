var imageForPreload=new Image();
var pagesPerEntity = new Array();
var commentStringToSet = "";
var searchvisible = false;
var gcse;
var showedImageVisible=false;
var showedImageSeed = 0;
var prevImageOpacity = 1.0;

function funcOnLoad(){
	if(document.getElementById('hidePlane')){
		document.getElementById('hidePlane').style.visibility='hidden';
		document.getElementById('hidePlaneDark').style.visibility='hidden';
		document.getElementById('advert_left').style.zIndex=1;
		document.getElementById('advert_right').style.zIndex=2;
		document.getElementById('main_div').style.zIndex=3;
	}
}

function showTip(intext){
	if(intext!=""){
		document.getElementById('tipDivID').style.left = window.event.clientX+window.pageXOffset+5+"px";
		document.getElementById('tipDivID').style.top =  window.event.clientY+window.pageYOffset+5+"px";
		document.getElementById('tipContentsDivID').innerText=intext;
		document.getElementById('tipDivID').style.visibility="visible";
	}
}

function moveTip(){
	document.getElementById('tipDivID').style.left = window.event.clientX+window.pageXOffset+5+"px";
	document.getElementById('tipDivID').style.top = window.event.clientY+window.pageYOffset+5+"px";
}

function hideTip(){
	document.getElementById('tipContentsDivID').innerText="";
	document.getElementById('tipDivID').style.visibility="hidden";
}

(function() {
var cx = '002790190076663355171:hqxemttarxe';
var gcse = document.createElement('script'); gcse.type = 'text/javascript'; gcse.async = true;
gcse.src = (document.location.protocol == 'https:' ? 'https:' : 'http:') +
	'//www.google.com/cse/cse.js?cx=' + cx;
var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(gcse, s);
})();

function swapsearch(){
	searchvisible = !searchvisible;
	
	var allsubdivs = document.getElementById('searchdiv').getElementsByTagName('div');
	if(searchvisible){
		for(var i=0;i<allsubdivs.length;i++){
			allsubdivs[i].style.visibility="visible";
		}
		
		document.getElementById("searchdiv").style.visibility="visible";
		document.getElementById("searchdiv").style.height="auto";
		
		document.getElementById('searchdiv').getElementsByTagName('input')[0].focus();
	}
	else{
		for(var i=0;i<allsubdivs.length;i++){
			allsubdivs[i].style.visibility="hidden";
		}
		document.getElementById("searchdiv").style.visibility="hidden";
		document.getElementById("searchdiv").style.height="0px";
		
		document.getElementById('searchdiv').getElementsByTagName('input')[0].blur();
	}
}

function setupsearch(tosearch){
	searchvisible = false;
	swapsearch();
	document.getElementById('searchdiv').getElementsByTagName('input')[0].value=tosearch;
}

function hideZoomedImg(isBg,event){
	if(isBg==true){
		document.getElementById("loadingImag").style.visibility="hidden";
		document.getElementById("imageComment").style.visibility="hidden";
		document.getElementById("fadePlane").style.visibility="hidden";
		
		document.getElementById("fadePlane").style.zIndex=1;
		
		document.getElementById("imageComment").innerHTML="";
		document.getElementById("showedImag").style.visibility="hidden";
		
		document.getElementById("showedImag").style.filter       = "alpha(opacity=100);";
		document.getElementById("showedImag").style.MozOpacity   = 1;
		document.getElementById("showedImag").style.opacity      = 1;
		document.getElementById("showedImag").style.KhtmlOpacity = 1;
		
		showedImageVisible = false;
	}
	else{
		if(event.target.id=="showedImag"){
			var start=event.target.src.lastIndexOf("/")+1;
			var end=event.target.src.length-5;
			var index=parseInt(event.target.src.substring(start,end));
			var newindex=index;
			
			var start2=event.target.src.lastIndexOf("/",start-2);
			var start3=event.target.src.lastIndexOf("/",start2-1);
			var folder = event.target.src.substring(start3+1,start2);
					
			if(event.offsetX<event.target.width/2){
				newindex=newindex-1;
				if(newindex<1){
					newindex=pagesPerEntity[curEntityNumber];
				}
			}
			else{
				newindex=newindex+1;
				if(newindex>pagesPerEntity[curEntityNumber]){
					newindex=1;
				};
			}
			
			if(newindex!=index){
				var ttt=event.target.src.substring(0,start-1);
				var ind=event.target.src.substring(ttt.lastIndexOf("/")+1,start-1);
				var newPath=folder +'/'+ind+'/'+newindex+'.jpg';
				showZoomedImg(newPath,curEntityNumber);
			}
			
			showedImageVisible = true;
		}
		else{
			document.getElementById("imageComment").innerHTML="";
			document.getElementById("showedImag").style.visibility="hidden";
		
			document.getElementById("loadingImag").style.visibility="hidden";
			document.getElementById("fadePlane").style.zIndex=1;
			document.getElementById("fadePlane").style.visibility="hidden";
			
			document.getElementById("showedImag").style.filter       = "alpha(opacity=100);";
			document.getElementById("showedImag").style.MozOpacity   = 1;
			document.getElementById("showedImag").style.opacity      = 1;
			document.getElementById("showedImag").style.KhtmlOpacity = 1;
			
			document.getElementById("imageComment").style.visibility="hidden";
			
			showedImageVisible = false;
		}
	}
}

function showLoadingImageIfRequired(seed)
{
	if(showedImageVisible && showedImageSeed == seed)
	{
		document.getElementById("loadingImag").style.visibility="visible";
	}
}

function increaseOpacity(seed)
{
	if(seed == showedImageSeed)
	{
		// set opacity of previous image
		document.getElementById("showedImag").style.filter       = "alpha(opacity="+(prevImageOpacity*100)+");";
		document.getElementById("showedImag").style.MozOpacity   = prevImageOpacity;
		document.getElementById("showedImag").style.opacity      = prevImageOpacity;
		document.getElementById("showedImag").style.KhtmlOpacity = prevImageOpacity;
		
		prevImageOpacity += 0.05;
		if(prevImageOpacity<1)
		{
			setTimeout( function(){ increaseOpacity(seed); }, 30);
		}
	}
}


function decreaseOpacity(seed)
{
	if(showedImageVisible && seed == showedImageSeed)
	{
		// set opacity of previous image
		document.getElementById("showedImag").style.filter       = "alpha(opacity="+(prevImageOpacity*100)+");";
		document.getElementById("showedImag").style.MozOpacity   = prevImageOpacity;
		document.getElementById("showedImag").style.opacity      = prevImageOpacity;
		document.getElementById("showedImag").style.KhtmlOpacity = prevImageOpacity;
		
		prevImageOpacity -= 0.025;
		if(prevImageOpacity>0.4)
		{
			setTimeout( function(){ decreaseOpacity(seed); }, 30);
		}
	}
}

function imageLoadedEvent(myHeight)
{
	showedImageSeed +=1;
	if(showedImageVisible){
		showedImageVisible = false;
		firstShow=false;
		
		document.getElementById("showedImag").src=imageForPreload.src;
		
		setTimeout( function(){ increaseOpacity(showedImageSeed); }, 30);
		
		document.getElementById("showedImagDiv").style.width=(document.getElementById("showedImag").width+4)+"px";
		document.getElementById("showedImagDiv").style.top=myHeight/2 - document.getElementById("showedImag").height/2+"px";
		
		document.getElementById("loadingImag").style.visibility="hidden";
		
		document.getElementById("imageComment").innerHTML=commentStringToSet;
		document.getElementById("imageComment").style.width=(document.getElementById("showedImag").width)+"px";
		
		document.getElementById("showedImag").style.visibility="visible";
		if(commentStringToSet==""){
			document.getElementById("imageComment").style.visibility="hidden";
		}
		else{
			document.getElementById("imageComment").style.visibility="visible";
		}
	}
}

function showZoomedImg(path,entityID){
	commentStringToSet="";
	for(var i=0;i<document.images.length;i++){
		if(document.images[i].src.search(path)!=-1){
			commentStringToSet=document.images[i].alt;
			break;
		}
	}

	curEntityNumber=entityID;
	var myWidth = 0, myHeight = 0;
	if( typeof( window.innerWidth ) == 'number' ){
		myWidth = window.innerWidth;
		myHeight = window.innerHeight;
	}
	else if( document.documentElement && ( document.documentElement.clientWidth || document.documentElement.clientHeight ) ) {
		//IE 6+ in 'standards compliant mode'
		myWidth = document.documentElement.clientWidth;
		myHeight = document.documentElement.clientHeight;
	}
	else if( document.body && ( document.body.clientWidth || document.body.clientHeight ) ) {
		//IE 4 compatible
		myWidth = document.body.clientWidth;
		myHeight = document.body.clientHeight;
	}
	
	document.getElementById("fadePlane").style.width=myWidth+"px";
	document.getElementById("fadePlane").style.height=myHeight+"px";
	document.getElementById("fadePlane").style.zIndex=40;
	document.getElementById("fadePlane").style.visibility="visible";
	
	// SET POSITION OF LOADING IMAGE
	if(firstShow){
		document.getElementById("loadingImag").style.top="100px";
	}
	else{
		document.getElementById("loadingImag").style.top=String(-parseInt(document.getElementById("showedImag").height, 10)/2-50)+"px";
	}
	
	showedImageVisible = true;
	
	// SET OPACITY OF LOADING IMAGE
	document.getElementById("sunLoadingImage").style.filter       = "alpha(opacity=100);";
	document.getElementById("sunLoadingImage").style.MozOpacity   = 1;
	document.getElementById("sunLoadingImage").style.opacity      = 1;
	document.getElementById("sunLoadingImage").style.KhtmlOpacity = 1;
		
	// ONLOAD
	imageForPreload.onload = function(){
		imageLoadedEvent(myHeight);
	}
	// ONERROR
	imageForPreload.onerror = function(){
		hideZoomedImg(false, null);
	}
	
	// CHANGE PATH
	imageForPreload.src=path.substring(0,path.length-4)+"f"+path.substring(path.length-4,path.length);
	// IF ALREADY LOADED
	if(imageForPreload.complete || imageForPreload.readyState == "complete"){
		imageLoadedEvent(myHeight);
	}
	else{ // SHOW LOADING IMAGE
		showedImageSeed++;
		if(showedImageSeed>1000)
		{
			showedImageSeed = 0;
		}
		prevImageOpacity = 1.0;
		setTimeout( function(){ decreaseOpacity(showedImageSeed); }, 30);
		setTimeout( function(){ showLoadingImageIfRequired(showedImageSeed); }, 60);
	}
}