<!doctype html>
<html>
<head>
   <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
   <meta http-equiv="refresh" content="5;URL=./" />
   <title>Ваше сообщение успешно отправлено</title>


</head>
 <style type="text/css">    
div {
    border: 11px outset;
    display: block;
    font-family: arial;
    font-stretch: semi-condensed;
    font-size: 25px;
    width: 50%;
    border-color: #4CAF50;
    background: #ece8c0;
    padding: 15px;
    border-radius: 15px;
    color: #584e4e;
}

div#SLG_balloon_obj {
    display: none !important;
}

h3 {
    font-size: 30px;
}
 </style>
<body style="background: radial-gradient(black 15%, transparent 16%) 0 0,  radial-gradient(black 15%, transparent 16%) 8px 8px,  radial-gradient(rgba(255,255,255,.1) 15%, transparent 20%) 0 1px,  radial-gradient(rgba(255,255,255,.1) 15%, transparent 20%) 8px 9px;background-color:#282828;background-size:16px 16px;color:#ffffff;">
 
<?php
   $back = "<p><a href=\"javascript: history.back()\">Вернуться назад</a></p>";
 
   if(!empty($_POST['name']) and !empty($_POST['phone']) 
   ){   
      $site = trim(strip_tags($_SERVER['HTTP_REFERER']));
      $name = trim(strip_tags($_POST['name']));
      $phone = trim(strip_tags($_POST['phone']));


      
      
 
      mail('mail@lp-base.pro', 'Заявка с сайта ' .$site, 
      '<br /> <strong>Имя:</strong> '.$name.
      '<br /> <strong>Телефон:</strong> '.$phone.
      '<br /> <strong>Сайт:</strong> '.$site,
      "Content-type:text/html;charset=utf-8");
 
      echo "<br /><center><div><h3>Ваша заявка успешно отправлена!</h3><Br> Мы свяжемся с Вами 
      ближайшее время.<Br><Br> Через 5 секунд Вы вернетесь <Br> на Главную страницу $back </div></center>";
 
      exit;
   } 
   else {
      echo "<br /><center><div><strong>Для отправки сообщения заполните все поля!</strong><Br> $back </div></center>";
      exit;
   }
?>
</body>
</html>