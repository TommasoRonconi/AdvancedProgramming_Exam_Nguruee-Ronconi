BEGIN {
    count=0;
    avg_tTu=0.;
    min_tTu=10000000000000.;
    max_tTu=0.;
    avg_tTo=0.;
    min_tTo=10000000000000.;
    max_tTo=0.;
    avg_tM=0.;
    min_tM=10000000000000.;
    max_tM=0.;
}
{
    ++count;
    avg_tTu+=$1;
    if ( $1 < min_tTu ) min_tTu=$1;
    if ( $1 > max_tTu ) max_tTu=$1;
    avg_tTo+=$2;
    if ( $2 < min_tTo ) min_tTo=$2;
    if ( $2 > max_tTo ) max_tTo=$2;
    avg_tM+=$3;
    if ( $3 < min_tM ) min_tM=$3;
    if ( $3 > max_tM ) max_tM=$3;
}
END {
    print run, "\t\t", min_tTu, "\t", avg_tTu/count, "\t", max_tTu, "\t", min_tTo, "\t", avg_tTo/count, "\t", max_tTo, "\t", min_tM, "\t", avg_tM/count, "\t", max_tM    
}
