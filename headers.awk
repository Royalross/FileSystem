NF > 0 {
    split($4, a, ".");
    goesin = a[1] ".nvs";
    printf("%s", $5) > goesin;
    line = "";
    for(i = 6; i <= NF; i++) {
        line = line " " $i;
    }
    split(line, b, "{");
    printf("%s;\n", b[1]) > goesin;
}
