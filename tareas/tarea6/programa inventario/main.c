#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NOMBRE_MAX 128
#define LINEA_MAX 512

typedef struct {
    int id;
    char nombre[NOMBRE_MAX];
    double precio;
    int cantidad;
} Producto;

typedef struct {
    Producto *datos;
    size_t n;
    size_t cap;
} Inventario;

static void quitar_nueva_linea(char *s) {
    if (!s) return;
    size_t n = strlen(s);
    while (n > 0 && (s[n-1] == '\n' || s[n-1] == '\r')) {
        s[n-1] = '\0';
        n--;
    }
}

static int leer_linea(const char *p, char *buf, size_t t) {
    if (p) {
        fputs(p, stdout);
        fflush(stdout);
    }
    if (!fgets(buf, (int)t, stdin)) return 0;
    quitar_nueva_linea(buf);
    return 1;
}

static int ui_preguntar_si_no(const char *p) {
    char r[16];
    for (;;) {
        if (!leer_linea(p, r, sizeof(r))) return 0;
        if (r[0]=='s'||r[0]=='S') return 1;
        if (r[0]=='n'||r[0]=='N') return 0;
        puts("Responda s o n.");
    }
}

static long leer_entero_rango(const char *p, long minv, long maxv) {
    char b[64];
    for (;;) {
        if (!leer_linea(p, b, sizeof(b))) continue;
        char *end = NULL;
        long v = strtol(b, &end, 10);
        if (end==b || *end!='\0') { puts("Ingrese un entero valido."); continue; }
        if (v < minv || v > maxv) {
            printf("Ingrese un valor en [%ld, %ld].\n", minv, maxv);
            continue;
        }
        return v;
    }
}

static double leer_double_min(const char *p, double minv) {
    char b[64];
    for (;;) {
        if (!leer_linea(p, b, sizeof(b))) continue;
        char *end = NULL;
        double v = strtod(b, &end);
        if (end==b || *end!='\0') { puts("Ingrese un numero."); continue; }
        if (v < minv) { printf("Ingrese un valor >= %.2f\n", minv); continue; }
        return v;
    }
}

static void inventario_init(Inventario *inv) {
    inv->datos = NULL;
    inv->n = 0;
    inv->cap = 0;
}

static void inventario_free(Inventario *inv) {
    free(inv->datos);
    inv->datos = NULL;
    inv->n = inv->cap = 0;
}

static int inventario_reservar(Inventario *inv, size_t nc) {
    if (nc <= inv->cap) return 1;
    size_t cap = inv->cap ? inv->cap : 8;
    while (cap < nc) cap *= 2;
    void *p = realloc(inv->datos, cap * sizeof(Producto));
    if (!p) return 0;
    inv->datos = (Producto*)p;
    inv->cap = cap;
    return 1;
}

static int inventario_agregar_producto(Inventario *inv, Producto p) {
    if (!inventario_reservar(inv, inv->n + 1)) return 0;
    inv->datos[inv->n++] = p;
    return 1;
}

static int es_encabezado(const char *l) {
    while (*l && isspace((unsigned char)*l)) l++;
    return isalpha((unsigned char)*l);
}

static int parsear_producto_csv(const char *linea, Producto *out) {
    char buf[LINEA_MAX];
    strncpy(buf, linea, sizeof(buf));
    buf[sizeof(buf)-1] = '\0';

    char *ctx = NULL;

    char *tok = strtok_r(buf, ",;\n\r", &ctx);
    if (!tok) return 0;
    char *end = NULL;
    long id = strtol(tok, &end, 10);
    if (end==tok) return 0;

    tok = strtok_r(NULL, ",;\n\r", &ctx);
    if (!tok) return 0;
    char nombre[NOMBRE_MAX];
    strncpy(nombre, tok, sizeof(nombre));
    nombre[NOMBRE_MAX-1] = '\0';

    tok = strtok_r(NULL, ",;\n\r", &ctx);
    if (!tok) return 0;
    end = NULL;
    double precio = strtod(tok, &end);
    if (end==tok) return 0;

    tok = strtok_r(NULL, ",;\n\r", &ctx);
    if (!tok) return 0;
    end = NULL;
    long cantidad = strtol(tok, &end, 10);
    if (end==tok) return 0;

    out->id = (int)id;
    out->precio = precio;
    out->cantidad = (int)cantidad;
    strncpy(out->nombre, nombre, sizeof(out->nombre));
    out->nombre[sizeof(out->nombre)-1] = '\0';

    return 1;
}

static int inventario_cargar(const char *r, Inventario *inv) {
    FILE *f = fopen(r, "r");
    if (!f) return 0;

    char linea[LINEA_MAX];
    int ln = 0;
    while (fgets(linea, sizeof(linea), f)) {
        ln++;
        int solo_ws = 1;
        for (char *p = linea; *p; ++p) if (!isspace((unsigned char)*p)) { solo_ws = 0; break; }
        if (solo_ws) continue;

        if (ln == 1 && es_encabezado(linea)) continue;

        Producto p;
        if (!parsear_producto_csv(linea, &p)) continue;

        if (!inventario_agregar_producto(inv, p)) {
            fclose(f);
            return -1;
        }
    }
    fclose(f);
    return 1;
}

static int inventario_guardar(const char *r, const Inventario *inv) {
    FILE *f = fopen(r, "w");
    if (!f) return 0;
    fprintf(f, "id,nombre,precio,cantidad\n");
    for (size_t i = 0; i < inv->n; ++i) {
        const Producto *p = &inv->datos[i];
        fprintf(f, "%d,%s,%.2f,%d\n", p->id, p->nombre, p->precio, p->cantidad);
    }
    fclose(f);
    return 1;
}

static int inventario_existe_id(const Inventario *inv, int id) {
    for (size_t i = 0; i < inv->n; ++i)
        if (inv->datos[i].id == id) return 1;
    return 0;
}

static int inventario_max_id(const Inventario *inv) {
    int m = 0;
    for (size_t i = 0; i < inv->n; ++i)
        if (inv->datos[i].id > m) m = inv->datos[i].id;
    return m;
}

static void inventario_imprimir(const Inventario *inv) {
    if (inv->n == 0) {
        puts("Inventario vacio.");
        return;
    }
    puts("=== Inventario ===");
    printf("%-6s | %-30s | %-10s | %-8s\n", "ID", "Nombre", "Precio", "Cant.");
    printf("-----------------------------------------------------------------\n");
    for (size_t i = 0; i < inv->n; ++i) {
        const Producto *p = &inv->datos[i];
        printf("%-6d | %-30.30s | %10.2f | %8d\n",
               p->id, p->nombre, p->precio, p->cantidad);
    }
}

static Producto ui_leer_producto_nuevo(const Inventario *inv) {
    Producto p;
    int sugerido = inventario_max_id(inv) + 1;
    printf("ID sugerido: %d\n", sugerido);
    long id = leer_entero_rango("Ingrese ID entero positivo: ", 1, 1000000000L);
    p.id = (int)id;
    if (inventario_existe_id(inv, p.id)) {
        printf("El ID %d ya existe. Se usara el sugerido %d.\n", p.id, sugerido);
        p.id = sugerido;
    }

    char nombre[NOMBRE_MAX];
    for (;;) {
        if (!leer_linea("Nombre: ", nombre, sizeof(nombre))) continue;
        if (strlen(nombre) == 0) continue;
        break;
    }
    strncpy(p.nombre, nombre, sizeof(p.nombre));
    p.nombre[sizeof(p.nombre)-1] = '\0';

    p.precio = leer_double_min("Precio mayor o igual a 0: ", 0.0);
    p.cantidad = (int)leer_entero_rango("Cantidad mayor o igual a 0: ", 0, 1000000000L);

    return p;
}

static void flujo_cargar_o_crear(const char *ruta, Inventario *inv) {
    int r = inventario_cargar(ruta, inv);
    if (r == 1) {
        printf("Se cargaron %zu productos desde %s.\n", inv->n, ruta);
    } else if (r == 0) {
        puts("No existe archivo de inventario. Se iniciara vacio.");
    } else {
        fprintf(stderr, "Error al cargar inventario.\n");
        exit(EXIT_FAILURE);
    }
}

static void flujo_agregar_si_quiere(const char *ruta, Inventario *inv) {
    if (!ui_preguntar_si_no("Desea agregar un producto s n: ")) return;

    Producto p = ui_leer_producto_nuevo(inv);
    if (!inventario_agregar_producto(inv, p)) {
        fprintf(stderr, "Memoria insuficiente.\n");
        exit(EXIT_FAILURE);
    }
    if (!inventario_guardar(ruta, inv)) {
        fprintf(stderr, "No se pudo guardar el inventario.\n");
        exit(EXIT_FAILURE);
    }
    puts("Producto agregado y archivo actualizado.");
}

static void flujo_imprimir_si_quiere(const Inventario *inv) {
    if (ui_preguntar_si_no("Desea imprimir los productos s n: ")) {
        inventario_imprimir(inv);
    }
}

int main(int argc, char *argv[]) {
    const char *ruta = (argc >= 2) ? argv[1] : "inventario.csv";

    Inventario inv;
    inventario_init(&inv);

    flujo_cargar_o_crear(ruta,&inv);
    flujo_agregar_si_quiere(ruta,&inv);
    flujo_imprimir_si_quiere(&inv);

    inventario_free(&inv);
    return 0;
}


