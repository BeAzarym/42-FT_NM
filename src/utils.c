
#include "../includes/ft_nm.h"

int compare_nm_style(const char *s1, const char *s2)
{
	char clean1[256], clean2[256];
	int i1 = 0, i2 = 0;
	
	for (const char *p = s1; *p && i1 < 255; p++) {
		if (*p != '_' && *p != '.' && *p != '@') {
			clean1[i1++] = *p;
		}
	}
	clean1[i1] = '\0';
	
	for (const char *p = s2; *p && i2 < 255; p++) {
		if (*p != '_' && *p != '.' && *p != '@') {
			clean2[i2++] = *p;
		}
	}
	clean2[i2] = '\0';
	
	const char *p1 = clean1;
	const char *p2 = clean2;
	
	while (*p1 && *p2)
	{
		unsigned char c1 = (unsigned char)*p1;
		unsigned char c2 = (unsigned char)*p2;
		
		if (c1 >= 'A' && c1 <= 'Z')
			c1 = c1 - 'A' + 'a';
		if (c2 >= 'A' && c2 <= 'Z')
			c2 = c2 - 'A' + 'a';
		
		if (c1 != c2)
			return (int)c1 - (int)c2;
			
		p1++;
		p2++;
	}

	unsigned char c1 = (unsigned char)*p1;
	unsigned char c2 = (unsigned char)*p2;
	if (c1 != c2)
		return (int)c1 - (int)c2;

	return ft_strcmp(s1, s2);
}