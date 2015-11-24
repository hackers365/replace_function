# replace_function
该php扩展提供重写函数的功能

#用法
<?php
function new_implode($seq, $list) {

    //....

    //hook
    
    return replace_implode($seq, $list);
}

//调用replace_function后。扩展将自动注册一个以'replace_'+ 原来函数名的函数。即以下自动注册'replace_implode'这个函数来提供被替换函数的功能。


replace_function('implode', 'new_implode');

?>


