#ifndef NODO_H
#define NODO_H


class Nodo
{
    private:
      int num;
      Nodo *sig;
    public:
        Nodo();
        void setDato(int num);
        int getDato();
        void setSiguiente(Nodo *sig);
        Nodo *getSiguiente();
        ~Nodo();

};

#endif // NODO_H