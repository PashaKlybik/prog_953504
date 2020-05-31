char mass[100];
int n = 0;

int len(char* str) {
    int l = 0;
    while (str[l] != '\n')
        l++;
    return l;
}

void Push(char c)
{
    mass[n++] = c;
}

char Pop()
{ 
    return mass[--n];
}

bool check(char c) {
    char raz[] = "!@#$%^&*()_+-={}[]:<>?,./ ";
    for (int i = 0; i < len(raz); i++)
        if (raz[i] == c)
            return false;
    return true;
}