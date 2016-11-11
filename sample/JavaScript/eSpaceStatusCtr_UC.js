/////W3 插件API.JS 由 eSDK开发部提供/////
function Browseris () {
	var agt=navigator.userAgent.toLowerCase();
	this.osver=1.0;
	if (agt)
	{
		var stOSVer=agt.substring(agt.indexOf("windows ")+11);
		this.osver=parseFloat(stOSVer);
	}
	this.major=parseInt(navigator.appVersion);
	this.nav=((agt.indexOf('mozilla')!=-1)&&((agt.indexOf('spoofer')==-1) && (agt.indexOf('compatible')==-1)));
	this.nav6=this.nav && (this.major==5);
	this.nav6up=this.nav && (this.major >=5);
	this.nav7up=false;
	if (this.nav6up)
	{
		var navIdx=agt.indexOf("netscape/");
		if (navIdx >=0 )
			this.nav7up=parseInt(agt.substring(navIdx+9)) >=7;
	}
	this.ie=(agt.indexOf("msie")!=-1);
	this.aol=this.ie && agt.indexOf(" aol ")!=-1;
	if (this.ie)
		{
		var stIEVer=agt.substring(agt.indexOf("msie ")+5);
		this.iever=parseInt(stIEVer);
		this.verIEFull=parseFloat(stIEVer);
		}
	else
		this.iever=0;
	this.ie4up=this.ie && (this.major >=4);
	this.ie5up=this.ie && (this.iever >=5);
	this.ie55up=this.ie && (this.verIEFull >=5.5);
	this.ie6up=this.ie && (this.iever >=6);
	this.winnt=((agt.indexOf("winnt")!=-1)||(agt.indexOf("windows nt")!=-1));
	this.win32=((this.major >=4) && (navigator.platform=="Win32")) ||	(agt.indexOf("win32")!=-1) || (agt.indexOf("32bit")!=-1);
	this.mac=(agt.indexOf("mac")!=-1);
	this.w3c=this.nav6up;
	this.safari=(agt.indexOf("safari")!=-1);
	this.safari125up=false;
	if (this.safari && this.major >=5)
	{
		var navIdx=agt.indexOf("safari/");
		if (navIdx >=0)
			this.safari125up=parseInt(agt.substring(navIdx+7)) >=125;
	}
}


var beSpaceStatusControlInited=false;
var browseris=new Browseris();
var bis=browseris;

function OneSpaceEvent(eventid)
{
    //alert(eventid);
}

var eSpaceStatusCtrl=null;
function EnsureeSpaceControl()
{
	if (!beSpaceStatusControlInited)
	{
		beSpaceStatusControlInited=true;
	    eSpaceStatusCtrl=document.createElement('object');
	    document.body.appendChild(eSpaceStatusCtrl);
	    eSpaceStatusCtrl.style.width = "0px";
	    eSpaceStatusCtrl.style.height = "0px";
		try 
		{
			eSpaceStatusCtrl.classid = "clsid:93A44D3B-7CED-454F-BBB4-EE0AA340BB78";
		} catch (e) {}
	eSpaceStatusCtrl.visible = "false";

	
	if (eSpaceStatusCtrl)
	{
		try
		{
			 eSpaceStatusCtrl.ShowUI(0,0,0);
		}
		catch(e)
		{
		
			 eSpaceStatusCtrl = null;
		}
	}
				
		if (eSpaceStatusCtrl)
		{
		   eSpaceStatusCtrl.OnUserStatusChange=eSpaceOnStatusChange;
		   eSpaceStatusCtrl.OneSpaceEvent=OneSpaceEvent;
		}
	}
	
        return eSpaceStatusCtrl;
}

var eSpaceAccountArr=null;
var eSpaceStaffNoArr=null;
var eSpaceNameArr=null;
var eSpaceStatusArr=null;//id,status

function eSpaceOnStatusChange(account, status, id)
{
    if (eSpaceStatusArr)
    {
        var img = eSpaceGetStatusImage(status);
        //alert(img.img);
        
        if (eSpaceStatusArr)
        {
            if (eSpaceStatusArr[id] != status)
		       {
			      eSpaceUpdateImage(id, img);
			      eSpaceStatusArr[id]=status;
		       }
        }
    }
}


function eSpaceUpdateImage(id, imgInfo)
{
	var obj=document.images(id);
	if (obj)
	{
		var img=imgInfo.img;
		var alt=imgInfo.alt;
		var oldImg=obj.src;
		var index=oldImg.lastIndexOf("/");
		var newImg=oldImg.slice(0, index+1);
		newImg+=img;
		if (oldImg==newImg && img !='blank.gif')
			return;
		if (obj.altbase)
		{
			obj.alt=obj.altbase;
		}
		else
		{
			obj.alt=alt;
		}
		var useFilter=browseris.ie &&browseris.ie55up &&(browseris.verIEFull < 7.0);
		var isPng=(newImg.toLowerCase().indexOf(".png") > 0);
		if (useFilter)
		{
			obj.style.filter="";
			obj.src=newImg;
		}
		else
		{
			obj.src=newImg;
		}
	}
}

function HideeSpaceCtrl()
{
    EnsureeSpaceControl();
    if (eSpaceStatusCtrl)
    {
	   eSpaceStatusCtrl.ShowUI(0, 0, 0);
    }
}

function ShoweSpaceCtrl()
{
	EnsureeSpaceControl();

	var obj=window.event.srcElement;
	var objSpan=obj;
	var objOOUI=obj;
	var oouiX=0, oouiY=0;
	var objRet=eSpaceGetOOUILocation(obj);
	objSpan=objRet.objSpan;
	objOOUI=objRet.objOOUI;
	
	//获取当前页面的缩放比例
	var zoom = screen.deviceXDPI / screen.logicalXDPI;
	// 将传递给espace activex控件的x，y值根据zoom缩放进行修正
	oouiX=objRet.oouiX * zoom;
	oouiY=objRet.oouiY * zoom;			

	if (eSpaceStatusCtrl)
		{     
		    var account = eSpaceAccountArr[objOOUI.id];
		    var staffno = eSpaceStaffNoArr[objOOUI.id];
		    var name = eSpaceNameArr[objOOUI.id];
		    var state = eSpaceStatusArr[objOOUI.id];

		    eSpaceStatusCtrl.SetUserInfo(account, staffno, name, state);
		    eSpaceStatusCtrl.ShowUI(-1, oouiX, oouiY); 
		}
		else
		{
		
		}
}


function eSpaceGetOOUILocation(obj)
{
	var objRet=new Object;
	var objSpan=obj;
	var objOOUI=obj;
	var oouiX=0, oouiY=0, objDX=0;
	var fRtl=document.dir=="rtl";
	while (objSpan && objSpan.tagName !="SPAN" && objSpan.tagName !="TABLE")
	{
		objSpan=objSpan.parentNode;
	}
	if (objSpan)
	{
		var collNodes=objSpan.tagName=="TABLE" ?	objSpan.rows(0).cells(0).childNodes :objSpan.childNodes;
		var i;
		for (i=0; i < collNodes.length;++i)
		{
			if (collNodes.item(i).tagName=="IMG" && collNodes.item(i).id)
			{
				objOOUI=collNodes.item(i);
				break;
			}
			if (collNodes.item(i).tagName=="A" &&collNodes.item(i).childNodes.length > 0 &&collNodes.item(i).childNodes.item(0).tagName=="IMG" &&	collNodes.item(i).childNodes.item(0).id)
			{
				objOOUI=collNodes.item(i).childNodes.item(0);
				break;
			}
		}
	}
	obj=objOOUI;
	while (obj)
	{
		if (fRtl)
		{
			if (obj.scrollWidth >=obj.clientWidth+obj.scrollLeft)
				objDX=obj.scrollWidth - obj.clientWidth - obj.scrollLeft;
			else
				objDX=obj.clientWidth+obj.scrollLeft - obj.scrollWidth;
			oouiX+=obj.offsetLeft+objDX;
		}
		else
			oouiX+=obj.offsetLeft - obj.scrollLeft;
		oouiY+=obj.offsetTop - obj.scrollTop;
		obj=obj.offsetParent;
	}
	try
	{
		obj=window.frameElement;
		while (obj)
		{
			if (fRtl)
			{
				if (obj.scrollWidth >=obj.clientWidth+obj.scrollLeft)
					objDX=obj.scrollWidth - obj.clientWidth - obj.scrollLeft;
				else
					objDX=obj.clientWidth+obj.scrollLeft - obj.scrollWidth;
				oouiX+=obj.offsetLeft+objDX;
			}
			else
				oouiX+=obj.offsetLeft - obj.scrollLeft;
			oouiY+=obj.offsetTop - obj.scrollTop;
			obj=obj.offsetParent;
		}
	} catch(e)
	{
	};

	//计算滚动条
	oouiX -= document.documentElement.scrollLeft;
	oouiY -= document.documentElement.scrollTop;
	objRet.objSpan=objSpan;
	objRet.objOOUI=objOOUI;
	objRet.oouiX=oouiX;
	objRet.oouiY=oouiY;
	if (fRtl)
	 {
		objRet.oouiX+=objOOUI.offsetWidth;
	 }
	return objRet;
}




function eSpaceGetStatusImage(state)
{
	var img="blank.gif";
	var alt="";
	switch (state)
	{
		case 0:
			img="offline.gif";
		break;

		case 1:
        		img="online.gif";
		break;
		case 2:
			img="offline.gif";
		break;
		case 3:
			img="busy.gif";
		break;
		case 4:
			img="leave.gif";
			break;
		case 5:
			img="NoDisturb.gif";
		break;		
	}
	var imageInfo =new eSpaceImageInfo();
	imageInfo.img=img;

	return imageInfo;
}

function eSpaceImageInfo()
{
	this.img=null;
}

function OneSpaceStatsCtrl(account, staffno, name, elem)
{	
	if (account==null || account=='')
		return;
	if (name==null || name=='')
		return;
	if (browseris.ie5up && browseris.win32)
	{	  
	        
		var obj=(elem) ? elem : window.event.srcElement;
		var objSpan=obj;
		var id=obj.id;
		var fFirst=false;
		if (!eSpaceAccountArr)
		{
			eSpaceAccountArr=new Object();
			eSpaceStaffNoArr=new Object();
			eSpaceNameArr=new Object();
			eSpaceStatusArr = new Object();
		}
		
		if (eSpaceAccountArr)
		{
			if (!eSpaceAccountArr[id])
			{
				eSpaceAccountArr[id]=account;

				fFirst=true;
			}
			if(!eSpaceStaffNoArr[id])
			{
			    eSpaceStaffNoArr[id]=staffno;
			}
			if(!eSpaceNameArr[id])
			{
			    eSpaceNameArr[id]=name;
			}
			
			if (eSpaceStatusArr[id]==null && typeof(eSpaceStatusArr[id])=="undefined")
			{
				eSpaceStatusArr[id]=0;
			}
			if ( fFirst && EnsureeSpaceControl())
			{
				var state=1, img;
				eSpaceGetStatus(account, id);
			}
		}

		if (fFirst)
		{
			var objRet=eSpaceGetOOUILocation(obj);
			objSpan=objRet.objSpan;
			if (objSpan)
			{
				objSpan.onmouseover=ShoweSpaceCtrl;
				objSpan.onfocusin=ShoweSpaceCtrl;
				objSpan.onmouseout=HideeSpaceCtrl;
				objSpan.onfocusout=HideeSpaceCtrl;
			}
		}
		
		fFirst=false;
	}
}

function eSpaceGetStatus(account, id)
{
  if(eSpaceStatusCtrl)
  {
    eSpaceStatusCtrl.GetStatus(account, id);//探测状态
  }
}

function eSpaceLogin(account, pwd, type)
{
  if(eSpaceStatusCtrl)
  {
    eSpaceStatusCtrl.Login(account, pwd, type);
  }
}



////添加鼠标滚轮事件，鼠标滚轮转动，将插件隐藏////
var scrollFunc=function(e)
	{
	  if (eSpaceStatusCtrl)
	    {
		  try
		  {
			 eSpaceStatusCtrl.ShowUI(0,0,0);
		  }
		catch(e)
		  {
		
			 eSpaceStatusCtrl = null;
		  }
	}
 }
/*注册事件*/
if(document.addEventListener){
     document.addEventListener('DOMMouseScroll',scrollFunc,false);
 }//W3C
 window.onmousewheel=document.onmousewheel=scrollFunc;//IE/Opera/Chrome