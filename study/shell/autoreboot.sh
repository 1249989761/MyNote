#! /bin/bash

fileName="autoreboot.sh"
homePath="/home/pi/autoreboot"
logPath="$homePath/log"
cfgPath="$homePath/cfg"
cfgFilePath="$cfgPath/autoreboot.ini"

isRunFlag=0
curCount=0
maxCount=0
minInterval=10
interval=$minInterval


#检测配置文件是否存在
checkConfigFile(){
    if [ -f $cfgFilePath ];then
        return 1
    else
        return 0
    fi
}

#解析配置文件
parseConfigFile(){
    checkConfigFile
    if [ $? -eq 1 ];then
        isRunFlag=$(sed -n 's/^isRunFlag=//p' $cfgFilePath)
        if [ -z "$isRunFlag" ];then
            isRunFlag=0
            echo "isRunFlag=0" >> $cfgFilePath
        fi

        curCount=$(sed -n 's/^curCount=//p' $cfgFilePath)
        if [ -z "$curCount" ];then
            curCount=0
            echo "curCount=0" >> $cfgFilePath
        fi

        maxCount=$(sed -n 's/^maxCount=//p' $cfgFilePath)
        if [ -z "$maxCount" ];then
            maxCount=10
            echo "maxCount=0" >> $cfgFilePath
        fi

        interval=$(sed -n 's/^interval=//p' $cfgFilePath)
        if [ -z "$interval" ];then
            interval=20
            echo "interval=20" >> $cfgFilePath
        fi

    else
        echo "cfg file not found"
        createConfigFile
    fi
}

#获取配置文件键值对信息
getMsg4ConfigFile(){
    key=$1
    value=$(grep -E "^$key=" $cfgFilePath | cut -d '=' -f2)
    echo $value
}

#更新配置文件键值对信息
updateMsg2ConfigFile(){
    key=$1
    value=$2
    preValue=$(getMsg4ConfigFile $key)
    
    if [ -z "$preValue" ]; then
        echo "$key=$value" >> $cfgFilePath
    else
        sed -i "s/$key=$preValue/$key=$value/g" $cfgFilePath
    fi
    
}

#创建配置文件
createConfigFile(){
    checkConfigFile
    if [ $? -eq 0 ];then
        mkdir -p $cfgPath
        touch $cfgFilePath
    fi
    echo "[rebootcfg]" > $cfgFilePath
    echo "isRunFlag=$isRunFlag" >> $cfgFilePath
    echo "curCount=$isRunFlag" >> $cfgFilePath
    echo "maxCount=$maxCount" >> $cfgFilePath
    echo "interval=$interval" >> $cfgFilePath
}


logtime_test(){
    finishTimeStamp=$(date +%s)
    START_TIME=$(echo -e "[$(date +%Y-%m-%d\ %H:%M:%S)]")
    echo $finishTimeStamp
    echo $START_TIME
}


#开始autoreboot测试
runReboot(){
    sudo reboot
}

start(){
    isRunFlag=1
    updateMsg2ConfigFile "isRunFlag" $isRunFlag
}

#停止autoreboot测试
stop(){
    isRunFlag=0
    updateMsg2ConfigFile "isRunFlag" $isRunFlag
    #log记录
}

help(){
    echo "------------------------------------------"
    echo "Autoreboot tool usage:"
    echo "[start]               开始测试"
    echo "[stop]                停止测试"
    echo "[help]                帮助手册"
    echo "[clear]               清除当前配置"
    echo "[setMaxCount][num]    设置最大reboot轮数"
    echo "[getMaxCount]         获取最大reboot轮数"
    echo "[setCurCount][num]    设置当前reboot轮数"
    echo "[getCurCount]         获取当前reboot轮数"
    echo "[setInterval][num]    设置时间间隔"
    echo "[getInterval]         获取时间间隔"
    echo "------------------------------------------"
}

#清空当前配置
clear(){
    isRunFlag=0
    curCount=0
    maxCount=0
    interval=30
}


setMaxCount(){
    maxCount=$1
    updateMsg2ConfigFile "maxCount" $maxCount
}


getMaxCount(){
    echo "----------------------------------"
    echo "Maximum Cycle:"$maxCount
    echo "----------------------------------"
}

setCurCount(){
    curCount=$1
    updateMsg2ConfigFile "curCount" $curCount
}


getCurCount(){
    echo "----------------------------------"
    echo "Current Cycle:"$curCount
    echo "----------------------------------"
}


setInterval(){
    interval=$1
    #保证重启后有足够安全时间去修改测试状态
    if [ $interval -lt $minInterval ];then
        echo "[WARNING]Reboot Interval is too low, minimum value is 10s"
        interval=$minInterval
    fi
    updateMsg2ConfigFile "interval" $interval
}


getInterval(){
    echo "----------------------------------"
    echo "Reboot Interval:"$interval
    echo "----------------------------------"
}



state(){
    echo "----------------------------------"
    if [ $isRunFlag -eq 1 ];then
        echo "State:Running"
    elif [ $isRunFlag -eq 0 ];then
        echo "State:Not Running"
    fi
    echo "Current Cycle:"$curCount
    echo "Maximum Cycle:"$maxCount
    echo "Reboot Interval:"$interval
    echo "----------------------------------"
}

parseConfigFile

if [ $# -gt 0 ];then
#用户输入程序
    #检测控制台输入
    if [ ! -f $cfgFilePath ];then
        createConfigFile
    fi

    case $1 in
        start)
            start
            ;;
        stop)
            stop
            ;;
        help)
            help
            ;;
        clear)
            clear
            createConfigFile
            ;;
        setMaxCount)
            if [ -z "$2" ];then
                echo "[ERROR]Param not set"
                exit
            fi
            setMaxCount $2
            exit
            ;;
        getMaxCount)
            getMaxCount
            exit
            ;;
        setCurCount)
            if [ -z "$2" ];then
                echo "[ERROR]Param not set"
                exit
            fi
            setCurCount $2
            exit
            ;;
        getCurCount)
            getCurCount
            exit
            ;;
        setInterval)
            if [ -z "$2" ];then
                echo "[ERROR]Param not set"
                exit
            fi
            setInterval $2
            exit
            ;;
        getInterval)
            getInterval
            exit
            ;;
        state)
            state
            exit
            ;;
        *)
            echo "[ERROR]Undefine param, query with param [help]"
            exit
            ;;
    esac
elif [ $# -eq 0 ];then
#开机自运行程序
    
    processCount=$(pgrep -c $fileName)
    echo "processCount="$processCount
    if [ $processCount -eq 1 ];then
        isRunFlag=1
        updateMsg2ConfigFile "isRunFlag" $isRunFlag
    elif [ $processCount -gt 1 ];then
        echo "[ERROR]Param is too low"
        exit
    fi

    while true; do
        ticker=0
        #获取最新配置信息
        value=$(getMsg4ConfigFile "curCount")
        if [ ! -z "$value" ];then
            curCount=$value
        fi

        value=$(getMsg4ConfigFile "maxCount")
        if [ ! -z "$value" ];then
            maxCount=$value
        fi

        value=$(getMsg4ConfigFile "interval")
        if [ ! -z "$value" ];then
            interval=$value
        fi

        #reboot倒计时
        if [ $curCount -lt $maxCount ];then
            while [ $ticker -lt $interval ];do
                sleep 1
                ticker=$(expr $ticker + 1)

                isRunFlag=$(getMsg4ConfigFile "isRunFlag")
                if [ $isRunFlag -eq 0 ];then
                    ticker=$(expr $ticker - 1)
                fi
            done

            curCount=$(expr $curCount + 1)
            updateMsg2ConfigFile "curCount" $curCount
            #write to cfg file
            runReboot
        else
            isRunFlag=0
            updateMsg2ConfigFile "isRunFlag" $isRunFlag
            sleep 1
        fi
    done
fi
