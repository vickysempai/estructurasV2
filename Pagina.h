#ifndef _PAGINA_H
#define	_PAGINA_H

class Pagina{
	public:
		Pagina(){}
		
		Pagina(int v,int k)
		{
			clave[k] = v;
		}
		
		Pagina(Pagina* p,int k)
		{
			rama[k] = p;
		}
		int cuenta = 0;
		int clave[4];
		Pagina* rama[5];
	friend class ArbolB;
};
#endif /* _PAGINA_H */
