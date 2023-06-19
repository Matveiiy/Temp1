function getRandomInt(min, max) {
    return Math.floor(Math.random() * (max - min + 1)) + min;
}
function shuffleArray(array) {
    var currentIndex = array.length, temporaryValue, randomIndex;

    while (0 !== currentIndex) {
        randomIndex = Math.floor(Math.random() * currentIndex);
        currentIndex -= 1;
        temporaryValue = array[currentIndex];
        array[currentIndex] = array[randomIndex];
        array[randomIndex] = temporaryValue;
    }

    return array;
}
var mainNow = 0;

function addTopLine(isMobile) {
    isMobile = isMobile ? isMobile : false;
    var allToday = new Date().getHours() * 100 + Math.floor(Math.random() * 1000);
    var now = mainNow != 0 ? mainNow : getRandomInt(45, 150);
    mainNow = now;
    var todayBuy = getRandomInt(50, 100) + new Date().getHours();
    if (allToday <= todayBuy) {
        todayBuy = Math.floor(allToday / 2) + 2;
    }
    var allHeight = isMobile ? 34 : 36;
    var html = '<style>.top-line span.mobile{height: 35px;padding-top: 10px;font-size: 12px !important;box-sizing: border-box;}' +
        'body{padding-top:34px !important;}' +
        '.top-line span{font-family: Arial !important;font-size:21px !important;}' +
        '.top-line .all-today.mobile{display:none;}' +
        '.tm-block-navbar{top: 36px !important;}' +
        '.all-today{background-image: url(//static.best-gooods.ru/img/all.png);height: 28px;padding-left: 45px;background-repeat: no-repeat;background-position: 5px;margin-left: 10px;display: inline-block;padding-top: 8px;margin-top: 0;}' +
        '.now{background-image: url(//static.best-gooods.ru/img/now.png);height: 28px;padding-left: 45px;background-repeat: no-repeat;background-position: 5px;margin-left: 10px;display: inline-block;padding-top: 8px;margin-top: 0;border-left: 3px solid #E4E4E4;}' +
        '.today-buy{background-image: url(//static.best-gooods.ru/img/buy.png);height: 28px;padding-left: 45px;background-repeat: no-repeat;background-position: 5px;margin-left: 10px;display: inline-block;padding-top: 8px;margin-top: 0;border-left: 3px solid #E4E4E4;}' +
        '.top-line .now.mobile{border-left:0;}</style>' +
        '<div class="top-line" style="overflow: hidden;box-sizing: border-box; z-index: 99999;height:'+allHeight+'px; text-align:center;background: #F1EDEE; position: fixed; width:100%;top:0; left:0;">' +
        '<div style="font-size: 21px;color: #000;display:inline-block;">' +
        '<span class="all-today '+(isMobile ? 'mobile' : '')+'">Посетителей сегодня: <strong>' + allToday + '</strong></span>' +
        '<span class="now '+(isMobile ? 'mobile' : '')+'">Сейчас на сайте: <strong>' + now + '</strong></span>' +
        '<span class="today-buy '+(isMobile ? 'mobile' : '')+'">Покупок сегодня: <strong>' + todayBuy + '</strong></span>' +
        '</div></div>';
    $(html).appendTo($(document.body));
}
function showSwimmer() {
    var count = mainNow != 0 ? mainNow : getRandomInt(45, 150);
    var bottom = 6;
    if ($('.delivery-notify').length) {
        bottom = 88;
    }
    mainNow = count;
    var html = '<div class="swimmer" style="font-family: Arial; font-size: 12px;z-index:991001;position: fixed; bottom:' + bottom + 'px;color:black;line-height: normal; left: 6px; width:265px;height: 73px;background: #FFFFEA; border-radius: 5px; border:1px solid #000; padding: 10px;box-sizing: border-box;">' +
        '<div class="close-swimmer" style="cursor:pointer;width: 13px;height: 13px;font-size: 22px;line-height: 0.65;position: absolute;top: 10px;right:10px; background: white;color:#9C8B74;border: 1px solid #9C8B74; border-radius: 3px;">&times;</div>' +
        '<img src="//static.best-gooods.ru/img/swimmer.png" style="width:50px; height: 50px; float: left;padding-right: 10px;border:0;">' +
        'Сейчас  ' + count + ' пользователей просматривают эту страницу вместе с вами.' +
        '</div>';
    $(html).appendTo($(document.body));
    $('.close-swimmer').on('click', function () {
        $('.swimmer').remove();
    });
    setInterval(function () {
        if ($('.delivery-notify').length) {
            $('.swimmer').css('bottom', 88);
        } else {
            $('.swimmer').css('bottom', 6);
        }
    }, 1000);
}
function freezeMoney(balance, dollar) {
    var html = '<style>' +
        '.freezing-info-packages {font-size: 20px;color: #000000;padding-top: 12px;z-index: 2;position: relative;line-height: 1;}' +
        '.freezing-close {position: absolute;top: -14px;right: 4px;width: 20px;height: 20px;display: block;}' +
        '.freezing-info:before {content: "";position: absolute;height: 198px;width: 280px;top: 0;right: 0;margin-top: -26px;background: url("//static.best-gooods.ru/img/buyer-ice.png") no-repeat;}' +
        '.freezing-info{font-family: Arial; z-index: 991000;color: black;width: 329px;height: 125px;position: fixed;background: url("//static.best-gooods.ru/img/buyer-bg.png") no-repeat;box-sizing: border-box;padding: 10px 30px;top:56px;right:0;border: 0;font-size: 100%;font: inherit;vertical-align: baseline;}' +
        '.freezing-info-price {font-size: 22px;color: #02aced;z-index: 2;position: relative;margin-left: 3px;}' +
        '.freezing-info-title {font-size: 21px;color: #000000;z-index: 2;position: relative;text-transform: uppercase;line-height: 1.3;}' +
        '.freezing-close:before {-webkit-transform: rotate(45deg);-ms-transform: rotate(45deg);transform: rotate(45deg);}' +
        '.freezing-close:after {-webkit-transform: rotate(-45deg);-ms-transform: rotate(-45deg);transform: rotate(-45deg);}' +
        '.freezing-close:before, ' +
        '.freezing-close:after {content: "";position: absolute;width: 100%;height: 2px;background: #ffffff;}' +
        '</style>' +
        '<div class="freezing-info">' +
        '<div class="freezing-info-title">Мы заморозили цену!</div>' +
        '<div class="freezing-info-price">1$ = <span class="dynamic-freezing-info--price">' + dollar + ' рублей</span></div>' +
        '<div class="freezing-info-packages">Осталось <span class="packages-count">' + balance + '</span> штук <br>по старому курсу' +
        '</div>' +
        '<a href="#close" class="freezing-close"></a>' +
        '</div>';
    $(html).appendTo($(document.body));
    $('.freezing-close').on('click', function (e) {
        $('.freezing-info').remove();
        e.preventDefault();
        e.stopPropagation();
    });
}

/*$(function(){
    let moveMouse = false;
    let scrollMouse = false;
    let keyDown = false;
    let setCookie = (document.cookie == "" ? false : true);

    $("html").mousemove(function(){
        moveMouse = true;
    });

    $("html").keydown(function() {
        keyDown = true;
    });

    $("form").submit(function() {
        $(this).append("<input type='hidden' name='moveMouse' value='"+moveMouse+"'>");
        $(this).append("<input type='hidden' name='keyDown' value='"+keyDown+"'>");
        $(this).append("<input type='hidden' name='setCookie' value='"+setCookie+"'>");
    });
});*/