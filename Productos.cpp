#include <iostream>
#include <fstream>
#include <cctype>

using namespace std;
// NOTA PARA MI*** no es necesario que cree el archivo de 
// .dat porque como ya lo inclui en el codigo, al momento de 
// compilarlo se va a crear automaticamente peroooooooo tambien lo puedo crear manualmente para 
//que se vea mas ordenado, pero no es necesario
// ===============================
// STRUCT
// ===============================
struct Producto {
    int codigo;
    char nombre[40];
    char categoria[30];
    int stock;
    float precio;
    bool activo;
};

// ===============================
// PROTOTIPOS DE FUNCIONES
// ===============================
void menu();
void registrarProducto();
void listarProductos();
void mostrarEncabezado();
void pausarSistema(); //(para que el sistema me de tiempo de ver los productos antes de que se cierre la consola, 
//y para que me deje volver al menu principal despues de mostrar los productos solo dando ENTER) 
//igual no e snecesario pero me gusta mas asi para que se vea mas ordenado y para que me de tiempo de ver 
//los productos antes de que se cierre la consola   
void convertirMinusculas(char texto[]) {
    for (int i = 0; texto[i] != '\0'; i++) {
        texto[i] = tolower(texto[i]);
    }
}//(es para que todo lo pnga en minusculas, para que se vea mas ordenado y para evitar problemas de mayusculas y minusculas al momento de buscar un producto por su nombre, por ejemplo si yo busco "manzana" y el producto esta registrado como "Manzana" no me lo va a encontrar, entonces con esta funcion convierto todo a minusculas para evitar ese problema)
// ===============================
// MAIN
// ===============================
int main() {
    menu();
    return 0;
}

// ===============================
// ENCABEZADO
// ===============================
void mostrarEncabezado() {
    cout << "\n===============================";
    cout << "\n SISTEMA DE VENTAS E INVENTARIO";
    cout << "\n===============================\n";
}

// ===============================
// PAUSA
// ===============================
void pausarSistema() {
    cout << "\nPresione ENTER para continuar...";
    cin.ignore();
    cin.get();
}

// ===============================
// MENU // ESTE MENU ME PERMITE ELEGIR ENTRE REGISTRAR UN PRODUCTO, LISTAR LOS PRODUCTOS O SALIR DEL PROGRAMA
// ===============================
void menu() {
    int opcion;
    do {
        mostrarEncabezado();
        cout << "\n1. Registrar producto";
        cout << "\n2. Listar productos";
        cout << "\n3. Salir";
        cout << "\n\nSeleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                registrarProducto();
                break; //(los break los puedo quitar perooo si lo quito va a correr todo el programa y no es lo que quiero
                //entonces con el break hago que se ejecute solo la opcion que elija y luego vuelva al menu principal)
                //por eso lo pongo despues de cada case para que se ejecute solo esa opcion**
            
                case 2:
                listarProductos();
                break;
            case 3:
                cout << "\nPrograma finalizado. Hasta luego.\n";
                break;
            default:
                cout << "\nOpcion invalida. Intente de nuevo.\n";
                pausarSistema();
        }
    } while (opcion != 3);
}

// ===============================
// REGISTRAR PRODUCTO
// ===============================
void registrarProducto() {
    Producto producto;
    ofstream archivo("productos.dat", ios::binary | ios::app);
//               Aquí se crea si no existe


    if (!archivo) {
        cout << "\nError: no se pudo abrir el archivo de productos.\n";
        return;
    }

    cout << "\n========== REGISTRO DE PRODUCTO ==========";

    cout << "\nCodigo: ";
    cin >> producto.codigo;
    cin.ignore();

    cout << "Nombre: ";
    cin.getline(producto.nombre, 40); convertirMinusculas(producto.nombre); // lo pongo asi para que se vea bonito 
    //y no todo mezclado aunque hay otra forma tambien de ponerlo sin tanto texto

    cout << "Categoria: ";
    cin.getline(producto.categoria, 30); convertirMinusculas(producto.categoria);
    // solo lo pongo en nombre y categoria porque el codigo es un numero y el stock tambien es un numero, 
    //entonces no tiene sentido convertirlos a minusculas

    cout << "Stock: ";
    cin >> producto.stock;

    cout << "Precio: ";
    cin >> producto.precio;

    // Campo activo: siempre true en este modulo
    producto.activo = true;

    // Escritura binaria
    archivo.write((char*)&producto, sizeof(producto));
    archivo.close();

    cout << "\nProducto registrado correctamente.\n";
    pausarSistema();
}

// ===============================
// LISTAR PRODUCTOS
// ===============================
void listarProductos() {
    Producto p;
    ifstream archivo("productos.dat", ios::binary);
//aca tambien se pone para que lo pueda guardar 
    if (!archivo) {
        cout << "\nNo existe informacion almacenada.\n";
        pausarSistema();
        return;
    }

    cout << "\n========== LISTADO DE PRODUCTOS ==========\n";

    bool hayProductos = false;

    while (archivo.read((char*)&p, sizeof(p))) {
        hayProductos = true;
        cout << "\n------------------------------------------";
        cout << "\nCodigo   : " << p.codigo;
        cout << "\nNombre   : " << p.nombre;
        cout << "\nCategoria: " << p.categoria;
        cout << "\nStock    : " << p.stock << " unidades";
        cout << "\nPrecio   : $" << p.precio;
        cout << "\nEstado   : " << (p.activo ? "Activo" : "Inactivo");
        cout << "\n------------------------------------------\n";
    }

    if (!hayProductos) {
        cout << "\nEl archivo no contiene productos registrados.\n";
    }

    archivo.close();
    pausarSistema();
    //este pausarsistema me sirve para que no se me cierre la consola al momento de mostrar los productos,
    //porque si no se cierra inmediatamente y no me da tiempo de verlos, aparte que si no se pausa
    //no me deja volver al menu principal, entonces con esto hago que se pause y me deje ver los productos 
    //y luego volver al menu
}


