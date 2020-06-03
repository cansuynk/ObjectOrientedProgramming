calico test file

--> "calico.yaml",  	runs the program once,
--> "calico2.yaml",	runs the program three times.

All the equals (=) in the test files are converted to colons (:), and the last script of the second file is converted to:

	Table3 ordered:
	We don't have enough bbq salad
	Tip is 0
	Total cost: 0 TL

Test files are working with the first version of stock.txt. The costs of menu items is rounded (as in PDF).

Although the outputs are correct in Calico, sometimes they pass all cases and sometimes not. 
In such a case: run with "calico calico.yaml --debug", and it gives no problem.
