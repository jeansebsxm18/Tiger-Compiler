#/bin/sh

GREEN='\e[32m'
RED='\e[31m'
BLUE='\e[36m'
YELLOW='\e[33m'
END='\e[0m'
BOLD=$(tput smso)
NOB=$(tput rmso)

#Path of tests directory
DIR="all_tests/*"

array=()

#Creation of the testerror file and initialization of variables
touch testerror
nbtest=0
nberr=0

prett=0

touch filerr
touch printerr

if test -f pretty_log.txt
then 
    rm pretty_log.txt
    touch pretty_log.txt
else
    touch pretty_log.txt
fi

#Browse all directories in tests directory
for d in $DIR
do
    code_err=0

    #Add '/*' to the path file"
    FILES="$d/*"
    #Remove what's before '*/' to the path file"
    dir="${d#*/}"

    #Print directory name
    echo -e "$BLUE============================================================================$END"
    echo -n "             $dir |" | tr '[:lower:]' '[:upper:]'

    case "$dir" in
        "scan")
            code_err=2
            ;;
        "syntax")
            code_err=3
            ;;
        "bind")
            code_err=4
            ;;
        "type")
            code_err=5
            ;;
    esac

    echo " Error code: $code_err"
    echo -e "$BLUE----------------------------------------------------------------------------$END"

    unique_nbtest=0
    unique_nberr=0

    #Browse all files
    for f in $FILES
    do
        case "$dir" in
            "scan")
                code_err=2
                ;;
            "syntax")
                code_err=3
                ;;
            "bind")
                code_err=4
                ;;
            "type")
                code_err=5
                ;;
            "good")
            code_err=0
                ;;
        esac

        code_prett=1
        fileee="${f##*/}"
        fileee=$(echo "$fileee" | cut -f 1 -d '.')

        pretty_file=$fileee"_pretty.txt"
        retour_pretty=$fileee"_retour.txt"

        touch $pretty_file
        touch $retour_pretty

        #GOOD
        if [ $code_err -eq 0 ]
        then

            ./../src/tc -XA $f >> $pretty_file 2>&1

            ./../src/tc -XA $pretty_file >> $retour_pretty 2>&1

            cmp -s $pretty_file $retour_pretty && code_prett=0 || code_prett=1

            ./../src/tc -X $retour_pretty >> filerr 2>&1
        
        #SCAN
        elif [ $code_err -eq 2 ]
        then
            ./../src/tc -X --parse $f >> filerr 2>&1  
        
        #SYNTAX
        elif [ $code_err -eq 3 ]
        then
            ./../src/tc -X --parse $f >> filerr 2>&1  
        
        #BIND
        elif [ $code_err -eq 4 ]
        then
            ./../src/tc -Xb --parse $f >> filerr 2>&1  
        
        #TYPE
        elif [ $code_err -eq 5 ]
        then
            ./../src/tc -T $f >> filerr 2>&1
        fi

        if [ $? -eq $code_err ]
        then
            if [ $code_err -eq 0 ]
            then
                if [ $code_prett -eq 0 ]
                then 
                    echo -e -n "$GREEN█$END "
                else
                    echo -e -n "$YELLOW█$END "
                    echo -e "$BLUE|$END$YELLOW PRETTY $END" $fileee >> printerr
                    prett=$(($prett + 1))
                fi
            else
                echo -e -n "$GREEN█$END "
            fi                
        else
            echo -e -n "$RED█$END "
            echo -e "$BLUE|$END$RED FAIL $END" $fileee >> printerr
            unique_nberr=$(($unique_nberr + 1))   
        fi

        unique_nbtest=$(($unique_nbtest + 1))
        if [ $(($unique_nbtest % 38)) -eq 0 ]
        then
            echo
            echo
        fi
        rm $pretty_file
        rm $retour_pretty
    done

    array+=("$unique_nberr")

    nbgood=$(($unique_nbtest - $unique_nberr))
    percen=$((($nbgood * 100) / $unique_nbtest))
    
    echo
    if [ $unique_nberr -ne 0 -o $prett -ne 0 ]
    then
        cat printerr
        echo "" > printerr
        echo
    else
        echo
    fi

    echo -ne "$BLUE##$END $dir: $nbgood / $unique_nbtest | $percen%"    
    if [ $unique_nberr -eq 0 ]
    then
        echo -e " -> $GREEN╰(★‿★)╯ $END"
    else
        echo -e " -> $RED（♯▼皿▼） $END"
    fi
    echo

    nbtest=$(($nbtest + $unique_nbtest))
    nberr=$(($nberr + $unique_nberr))
done

echo -e "$BLUE============================================================================$END"
echo -e "$BLUE|                     TIGER TESTSUIT                       |$END"
echo -e "$BLUE============================================================================$END"

echo

echo -e "-$GREEN""PASS ""█$END"
echo -e "-$RED""FAIL ""█$END"
echo -e "-$YELLOW""PRETTY PRINT ""█$END"
echo 

nbgood=$(($nbtest - $nberr))

echo "# TOTAL: $nbtest"
echo -en "#$GREEN PASS:  $nbgood$END"

if [ $prett -eq 0 ]
then
    echo
else
    echo -e "$YELLOW  PRETTY:  $prett$END"
fi
echo -e "#$RED FAIL:  $nberr$END"

echo
percen=$((($nbgood * 100) / $nbtest))
echo -n "# You pass: "

#Loading bar
for val in ${array[@]}
do
    if [ $val -eq 0 ]
    then
            echo -e -n "$GREEN█$END "
    else
            echo -e -n "$RED█$END "
    fi
done
echo -n "$percen%"

if [ $percen -eq 100 ]
    then
        echo -e " -> $GREEN╰(★‿★)╯ $END"
    else
        echo -e " -> $RED（♯▼皿▼） $END"
fi

echo
rm testerror
rm filerr
rm printerr

if [ $percen -gt 30 ]
then
    exit 0
else
    exit 1
fi
