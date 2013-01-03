#include "control.h"
#include "paint.h"
#include <iostream>

int	main(int argc, char** argv)
{
	Paint	id_paint;

	if (argc <= 2)
	{
		if (id_paint.Init(argc, argv))
			return 1;
		id_paint.Run();
	}
	else
		std::cout << "SYNOPSIS: id_paint [file]" << std::endl;
	return (0);
}
