#include "../minishell.h"

static char	**free_array(char **ptr, int i)
{
	while (i > 0)
	{
		i--;
		free(ptr[i]);
	}
	free(ptr);
	return (0);
}

int		word_counter(char *input)
{
	int		i;
	int		count;
	bool	in_quote;
	bool	in_word;
	char 	*str;

	str = "<>| \0";
	i = 0;
	count = 0;
	in_quote = false;
	in_word = false;
	while (input[i] == ' ')
		i++;
	while (input[i])
	{
		if (input[i] == 34)
			in_quote = !in_quote;
		if (!in_quote)
		{
			if (ft_strchr(str, input[i]))
			{
				if (input[i] != ' ')
				{
					count++;
					in_word = false;
				}
			}
			else if (!in_word)
			{
				in_word = true;
				count++;
			}
		}
		i++;
	}
	printf("%d-*-*-*-\n", count);
	return (count);
}

char	*put_word(char *word, char *input, int start, int word_len)
{
	int j = 0;
	int k = start;

	while (word_len > 0)
	{
		word[j] = input[k];
		j++;
		k++;
		word_len--;
	}
	word[j] = '\0';
	return (word);
}

char	**split_words(char *input, char **str, unsigned int word_count)
{
	int		i = 0;
	int		word = 0;
	int		word_len = 0;
	bool	in_quote = false;
	char	*chars;

	chars = "<>| \0";
	while (word < word_count)
	{
		while (input[i] && input[i] == ' ' && !in_quote)
			i++;
		int start = i;
		while (input[i] && (!ft_strchr(chars, input[i]) || in_quote))
		{
			if (input[i] == 34)
				in_quote = !in_quote;
			word_len++;
			i++;
		}
		// Eğer özel bir karakterle karşılaşırsan, tek başına bir kelime olmalı
		if (ft_strchr(chars, input[i]) && !in_quote && word_len == 0)
		{
			word_len = 1;
			i++;
		}
		str[word] = (char *)malloc((sizeof(char) * (word_len + 1)));
		printf("wordlen: %d\n", word_len);
		put_word(str[word], input, start, word_len);
		word_len = 0;
		word++;
	}
	str[word] = 0;
	return str;
}

char	**split_by_real_spaces(char *input)
{
	unsigned int	word_count;
	char			**str;
	int 			i;

	i = 0;
	word_count = word_counter(input);
	str = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!str)
		return (0);
	str = split_words(input, str, word_count);
	while (str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}
	return (str);
}