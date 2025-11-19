/* ************************************************************************** */
/* */
/* TEST BENCH - C03                                                         */
/* Guarda esto como: main.c en la raiz de tu proyecto                       */
/* */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* --- PROTOTIPOS (Asegurate que coinciden con tus ejercicios) --- */
int				ft_strncmp(const char *s1, const char *s2, unsigned int n);
char			*ft_strcat(char *dest, char *src);
char			*ft_strncat(char *dest, char *src, unsigned int nb);
char			*ft_strstr(char *str, char *to_find);
unsigned int	ft_strlcat(char *dest, char *src, unsigned int size);

/* --- COLORES PARA VISUALIZACION --- */
#define GREEN "\033[0;32m"
#define RED   "\033[0;31m"
#define CYAN  "\033[0;36m"
#define RESET "\033[0m"

void print_title(char *title)
{
	printf("\n%s=== PROBANDO: %s ===%s\n", CYAN, title, RESET);
}

int main(void)
{
	/* --------------------------------------------------------- */
	/* TEST FT_STRNCMP                     */
	/* --------------------------------------------------------- */
	print_title("ft_strncmp");
	
	printf("1. Iguales (n=5):      %d \t(Esperado: 0)\n", ft_strncmp("Hello", "Hello", 5));
	printf("2. Diferentes (n=5):   %d \t(Esperado: != 0)\n", ft_strncmp("Hello", "Hella", 5));
	printf("3. Limite n (n=3):     %d \t(Esperado: 0)\n", ft_strncmp("Hello", "Hella", 3));
	printf("4. Strings vacios:     %d \t(Esperado: 0)\n", ft_strncmp("", "", 5));
	printf("5. n es cero:          %d \t(Esperado: 0)\n", ft_strncmp("ABC", "XYZ", 0));
	// TEST CRITICO: UNSIGNED CHAR
	// '\200' es 128. 'A' es 65. 128 > 65. Resultado debe ser positivo.
	// Si da negativo, estas usando char (con signo) en vez de unsigned char.
	printf("6. Extended ASCII:     %d \t(Esperado: > 0) -> Comparando 'A' vs '\\200'\n", ft_strncmp("\200", "A", 1));


	/* --------------------------------------------------------- */
	/* TEST FT_STRCAT                     */
	/* --------------------------------------------------------- */
	print_title("ft_strcat");
	
	char buff_cat[50] = "Hola ";
	ft_strcat(buff_cat, "Mundo");
	printf("1. Basico:             '%s' \t(Esperado: 'Hola Mundo')\n", buff_cat);
	
	char buff_cat2[50] = "Test";
	ft_strcat(buff_cat2, "");
	printf("2. Source vacio:       '%s' \t(Esperado: 'Test')\n", buff_cat2);


	/* --------------------------------------------------------- */
	/* TEST FT_STRNCAT                     */
	/* --------------------------------------------------------- */
	print_title("ft_strncat");
	
	char buff_ncat[50] = "Hola ";
	ft_strncat(buff_ncat, "Mundo", 3);
	printf("1. Cortar n (3):       '%s' \t(Esperado: 'Hola Mun')\n", buff_ncat);
	
	char buff_ncat2[50] = "Test";
	ft_strncat(buff_ncat2, "123", 10);
	printf("2. n > len_src:        '%s' \t(Esperado: 'Test123')\n", buff_ncat2);

	char buff_ncat3[50] = "Test";
	ft_strncat(buff_ncat3, "XYZ", 0);
	printf("3. n es 0:             '%s' \t(Esperado: 'Test')\n", buff_ncat3);


	/* --------------------------------------------------------- */
	/* TEST FT_STRSTR                     */
	/* --------------------------------------------------------- */
	print_title("ft_strstr");
	
	char *haystack = "Busca la aguja en el pajar";
	char *res;

	res = ft_strstr(haystack, "aguja");
	printf("1. Encontrado:         '%s'\n", res ? res : "NULL");
	
	res = ft_strstr(haystack, "piedra");
	printf("2. No encontrado:      '%s' \t(Esperado: NULL)\n", res ? res : "NULL");
	
	// TEST CRITICO: Aguja vacía
	res = ft_strstr(haystack, "");
	printf("3. Aguja vacia:        '%s'\n", res);
	if (res == haystack) printf("   -> %s[OK] Puntero retornado es igual al original.%s\n", GREEN, RESET);
	else printf("   -> %s[KO] Debes retornar str si to_find es vacio.%s\n", RED, RESET);


	/* --------------------------------------------------------- */
	/* TEST FT_STRLCAT                     */
	/* --------------------------------------------------------- */
	print_title("ft_strlcat");
	
	char buff_lcat[20] = "12345"; // len = 5
	unsigned int ret;

	// Caso 1: Espacio suficiente
	// size = 20. Dest = 5. Src = 3 ("ABC"). Total deseado = 8.
	ret = ft_strlcat(buff_lcat, "ABC", 20);
	printf("1. Espacio OK:         '%s' | Ret: %u (Exp: 8)\n", buff_lcat, ret);

	// Caso 2: Truncamiento
	// buff tiene "12345ABC". size pasamos 8. Len actual es 8. Quiero meter "ZZ".
	// Como size (8) == len (8), no copia nada y retorna size + len_src (8+2=10).
	strcpy(buff_lcat, "12345");
	ret = ft_strlcat(buff_lcat, "ABC", 7); 
	// size 7. dest tiene 5. Copiara solo 1 char para dejar espacio al \0.
	printf("2. Truncate:           '%s' | Ret: %u (Exp: 8)\n", buff_lcat, ret);

	// Caso 3: Size < strlen(dest)
	// Este es el caso que rompe todo.
	// Dest = "12345" (len 5). Size pasamos 3.
	// No debe tocar la string. Debe retornar size + len(src) -> 3 + 3 = 6.
	strcpy(buff_lcat, "12345");
	ret = ft_strlcat(buff_lcat, "ABC", 3);
	printf("3. Size < LenDest:     '%s' | Ret: %u (Exp: 6)\n", buff_lcat, ret);

	printf("\n");
	return (0);
}
