void encrypt(char *m)
{
        char *c;

        for (c = m; *c != '\0'; c++) {
                *c = *c ^ 31;
        }
}
