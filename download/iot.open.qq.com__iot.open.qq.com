<!DOCTYPE html>
<html>

<head>
    <meta http-equiv="X-UA-Compatible" content="IE=Edge" />
    <meta charset="utf-8">
    <title>QQ物联智能硬件开放平台</title>
    <meta name="Keywords" content="QQ物联智能硬件开放平台，QQ物联，智能硬件平台，腾讯智能硬件，腾讯物联，智能硬件，腾讯开放平台" />
    <meta name="Description" content="QQ物联智能硬件开放平台，简称“QQ物联”，是腾讯全新推出的面向物联网领域的开放合作平台，旨在帮助智能硬件设备实现与用户、与设备、与服务间的互联互动，进而为用户带来更具智慧化的服务和更具人性化的体验、为厂商带来更具竞争力的产品和更可观的销售量，QQ物联致力于帮助传统企业成功实现互联网转型。"
    />
    <script type="text/javascript">
        document.domain = 'qq.com';
    </script>
    <base href="//qzonestyle.gtimg.cn/open_proj/proj-hardware/html/" />
    <link rel="stylesheet" type="text/css" href="../global.css">
    <link rel="stylesheet" type="text/css" href="../index-new.css" />
    <style>
        .banner .b-main .b-des {
            margin: 20px 0;
        }

        .btn-test-big:hover {
            background: #bcbcbc;
        }

        .business-off-tip {
            width: 100%;
            text-align: center;
            margin: 14px 0;
            color: #ff6e0d;
            font-size: 18px;
        }
    </style>
</head>

<body>
    <div class="banner">
        <div class="header" id="header-wrapper">
	<div class="h-main clear-fix">
		<a href="//iot.open.qq.com/" class="logo"><img src="//imgcache.qq.com/open_proj/proj-hardware/img/index-new/new-logo-new.png"></a>
		<div class="nav-box tab-2">
			<ul class="nav-ul clear-fix" id="iot-nav">
				<li data-mod="index">
					<a href="//iot.open.qq.com/" class="tab">首页</a>
				</li>
				<li data-mod="introduction">
					<a href="//iot.open.qq.com/introduction" class="tab">平台介绍</a>
				</li>
				<li data-mod="cooperation">
					<a href="//iot.open.qq.com/cooperation" class="tab">合作伙伴</a>
				</li>
				<li data-mod="wiki">
					<a href="//iot.open.qq.com/wiki/index.html" class="tab">资料库</a>
				</li>
				
					<li data-mod="home-reg">
						<a href="//iot.open.qq.com/home/list" class="tab" _hot_tag="iot-open.xx.top-apply-test.zly141029">申请公测</a>
					</li>
				
			</ul>
		</div>
		
			<div class="login-box nologin">
				<a href="javascript:void(0);" class="btn js-btn-login">登录</a>
			</div>
		
	</div>
</div>
        <div class="b-main">
            <div class="topic">无限连接无限想象</div>
            <div class="b-des">2014年10月，“QQ物联智能硬件开放平台”发布，将QQ账号体系及关系链、QQ消息通道能力等核心能力，提供给可穿戴设备、智能家居、智能车载、传统硬件等领域合作伙伴，实现用户与设备及设备与设备之间的互联互通互动，充分利用和发挥腾讯QQ的亿万手机客户端及云服务的优势，更大范围帮助传统行业实现互联网化。</div>
            
            <a onclick="document.getElementById('js-business-off-tip1').style.display = 'block'" class="btn-test-big" _hot_tag="iot-open.xx.banner-apply-test.zly141029">申请公测
                <i class="shadow"></i>
            </a>
            <div class="business-off-tip" id="js-business-off-tip1" style="display: none">由于平台调整，暂停接入申请</div>
            
            <!-- <span class="download-box">
                    <a href="//iot.open.qq.com/introduction#menu-5" class="down-simple down-doc"><i></i><span>产品案例</span></a>
                    <a href="//iot.open.qq.com/wiki/index.html" class="down-simple down-file"><i></i><span>开发者资料</span></a>
                </span> -->
        </div>
    </div>
    <div class="abilities" id="abilities-wrapper">
        <ul class="ab-list clear-fix">
            <li class="ab-item ab-item-1 current" id="ab-item-1">
                <i class="ico">
                    <i></i>
                </i>
                <p class="ab-tit">创新产品能力</p>
                <p class="ab-des">合作伙伴基于腾讯核心资源打造与竞品的差异化，让产品更有竞争力</p>
                <i class="bor">
                    <i class="bor-i"></i>
                </i>
            </li>
            <li class="ab-item ab-item-2" id="ab-item-2">
                <i class="ico">
                    <i></i>
                </i>
                <p class="ab-tit">降低研发成本</p>
                <p class="ab-des">腾讯开放云、管、端的优势能力及资源，解决合作伙伴的基础研发需要</p>
                <i class="bor">
                    <i class="bor-i"></i>
                </i>
            </li>
            <li class="ab-item ab-item-3" id="ab-item-3">
                <i class="ico">
                    <i></i>
                </i>
                <p class="ab-tit">扩大社交影响</p>
                <p class="ab-des">腾讯的品牌及营销优势与用户间的社交传播，助力提升合作伙伴的影响力</p>
                <i class="bor">
                    <i class="bor-i"></i>
                </i>
            </li>
        </ul>
    </div>
    <div class="ab-detail-wrapper">
        <div class="adl-wrapper">
            <div class="ab-detail-list">
                <div class="ab-item-detail" id="ab-item-detail-1">
                    <div class="m-ab">
                        <img src="../img/index-new/p1-1.jpg" class="img" alt="">
                        <p class="m-ab-tit">
                            <i class="dot"></i>设备与设备更易“沟通”
                        </p>
                        <p class="m-ab-des">
                            腾讯通用开放协议让跨品牌设备实现互联互通，平台上的大家都可成为彼此的合作伙伴，优势可互补，资源可互利，联合实现共赢
                        </p>
                    </div>
                    <div class="m-ab odd">
                        <img src="../img/index-new/p1-2.jpg" class="img" alt="">
                        <p class="m-ab-tit">
                            <i class="dot"></i>设备与用户更好互动
                        </p>
                        <p class="m-ab-des">
                            QQ社交关系链给予产品全新的跨用户互动体验，多人互动创新设备更多功能和价值，让设备更好的融入到家庭、办公、公共生活中去
                        </p>
                    </div>
                    <div class="m-ab">
                        <img src="../img/index-new/p1-3.jpg" class="img" alt="">
                        <p class="m-ab-tit">
                            <i class="dot"></i>设备更加“聪明”
                        </p>
                        <p class="m-ab-des">
                            海量服务内容结合智能推荐算法，让设备富有人性；尖端模式识别结合腾讯大数据，让设备充满智慧
                        </p>
                    </div>
                    <div class="m-ab odd">
                        <img src="../img/index-new/p1-4.jpg" class="img" alt="">
                        <p class="m-ab-tit">
                            <i class="dot"></i>设备更多可能
                        </p>
                        <p class="m-ab-des">
                            腾讯开放平台众多应用开发者基于腾讯通用开放协议可为设备开发更多功能服务、开启更多应用场景、深挖更多商业价值，开放成就梦想
                        </p>
                    </div>
                </div>
                <div class="ab-item-detail" id="ab-item-detail-2" style="display:none;">
                    <div class="m-ab">
                        <img src="../img/index-new/p2-1.jpg" class="img" alt="">
                        <p class="m-ab-tit">
                            <i class="dot"></i>软件开发及推广成本更低
                        </p>
                        <p class="m-ab-des">
                            QQ账号体系、消息及富媒体传输通道、轻App等能力一应俱全，既可降低基础能力的研发投入，还可保证稳定可靠的使用体验，让合作伙伴可集中资源进行核心能力的研发
                        </p>
                    </div>
                    <div class="m-ab odd">
                        <img src="../img/index-new/p2-2.jpg" class="img" alt="">
                        <p class="m-ab-tit">
                            <i class="dot"></i>云端部署及运维成本更低
                        </p>
                        <p class="m-ab-des">
                            高性价比、百分服务、安全稳定