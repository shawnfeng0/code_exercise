#!/bin/bash

# 表达式：
# var1=$[$var1+1]

if [ $# -ne 0 ] ; then # 有参数

    if [ $1 == "--clear" ]; then
        rm 00[0-4][0-9].bin 2> /dev/null
        exit 0
    else
        echo "invalid option"
        echo "usage: fibonacci [--clear]"
        exit 1
    fi
fi

# 初始化
file_name_1='0001.bin'
file_name_2='0002.bin'
cat /dev/urandom | head -c 1 > $file_name_1 # 写入固定数量的随机字符
cat /dev/urandom | head -c 1 > $file_name_2

for (( i = 3; i <= 45; i++)); do

    file_name=00$[$i/10]$[$i%10].bin # 生成对应文件名
    touch $file_name # 创建文件

    cat $file_name_1 > $file_name # 复制
    cat $file_name_2 >> $file_name # 追加

    # 循环赋值
    file_name_2=$file_name_1
    file_name_1=$file_name

    # DEBUG
    echo -n "$i: "
    date
done

exit 0