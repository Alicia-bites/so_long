int	ft_check_elts(t_list *lst)
{
	t_list	*iterator;
	
	iterator = lst;
	while (iterator)
	{
		if (ft_strchr(iterator->line, '1') == 0)
			return (ft_panic(INVALID_ARG));
		if (ft_strchr(iterator->line, '0') == 0)
			return (ft_panic(INVALID_ARG));
		if (ft_strchr(iterator->line, 'P') == 0)
			return (ft_panic(INVALID_ARG));
		if (ft_strchr(iterator->line, 'E') == 0)
			return (ft_panic(INVALID_ARG));
		if (ft_strchr(iterator->line, 'C') == 0)
			return (ft_panic(INVALID_ARG));
		if (ft_strchr(iterator->line, '\n') == 0)
			return (ft_panic(INVALID_ARG));
		iterator = iterator->next;
	}
}