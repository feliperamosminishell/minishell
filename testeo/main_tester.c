#include "minishell.h"
#include <stdio.h>
#include <string.h>

// Colores para output
#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[1;31m"
#define COLOR_GREEN   "\033[1;32m"
#define COLOR_BLUE    "\033[1;34m"
#define COLOR_YELLOW  "\033[1;33m"

void print_test_header(char *name)
{
    printf("\n%s=== TEST: %s ===%s\n", COLOR_BLUE, name, COLOR_RESET);
}

void print_separator(void)
{
    printf("%s----------------------------------------%s\n", COLOR_YELLOW, COLOR_RESET);
}

// Helper para verificar si env contiene una variable
int env_contains(t_env *env, char *key)
{
    while (env)
    {
        if (strcmp(env->key, key) == 0)
            return (1);
        env = env->next;
    }
    return (0);
}

// Helper para obtener valor de env
char *get_env_value(t_env *env, char *key)
{
    while (env)
    {
        if (strcmp(env->key, key) == 0)
            return (env->value);
        env = env->next;
    }
    return (NULL);
}

// Helper para imprimir primeros N elementos de env
void print_n_env(t_env *env, int n)
{
    int i = 0;
    while (env && i < n)
    {
        if (env->value)
            printf("%s=%s\n", env->key, env->value);
        env = env->next;
        i++;
    }
}

void test_echo(void)
{
    print_test_header("ECHO");
    
    // Test 1: Echo básico
    printf("Test 1 - Echo básico:\n");
    char *echo_1[] = {"echo", "hola", "mundo", NULL};
    printf("Expected: hola mundo\\n\nActual:   ");
    int ret = builtin_echo(echo_1);
    printf("Return value: %d\n", ret);
    print_separator();

    // Test 2: Flag -n
    printf("Test 2 - Flag -n:\n");
    char *echo_2[] = {"echo", "-n", "sin", "newline", NULL};
    printf("Expected: sin newline (sin \\n)\nActual:   ");
    ret = builtin_echo(echo_2);
    printf("\nReturn value: %d\n", ret);
    print_separator();

    // Test 3: Flag -n repetida
    printf("Test 3 - Flag -n repetida:\n");
    char *echo_3[] = {"echo", "-nnnnnn", "flag", "repetida", NULL};
    printf("Expected: flag repetida (sin \\n)\nActual:   ");
    ret = builtin_echo(echo_3);
    printf("\nReturn value: %d\n", ret);
    print_separator();

    // Test 4: Múltiples flags -n
    printf("Test 4 - Múltiples flags -n:\n");
    char *echo_4[] = {"echo", "-n", "-n", "-n", "test", NULL};
    printf("Expected: test (sin \\n)\nActual:   ");
    ret = builtin_echo(echo_4);
    printf("\nReturn value: %d\n", ret);
    print_separator();

    // Test 5: Solo echo
    printf("Test 5 - Solo echo:\n");
    char *echo_5[] = {"echo", NULL};
    printf("Expected: \\n\nActual:   ");
    ret = builtin_echo(echo_5);
    printf("Return value: %d\n", ret);
    print_separator();

    // Test 6: Echo vacío con -n
    printf("Test 6 - Echo -n sin argumentos:\n");
    char *echo_6[] = {"echo", "-n", NULL};
    printf("Expected: (nada, sin \\n)\nActual:   ");
    ret = builtin_echo(echo_6);
    printf("[END]\nReturn value: %d\n", ret);
    print_separator();

    // Test 7: Flag -n inválida
    printf("Test 7 - Flag -n con otros caracteres:\n");
    char *echo_7[] = {"echo", "-na", "test", NULL};
    printf("Expected: -na test\\n\nActual:   ");
    ret = builtin_echo(echo_7);
    printf("Return value: %d\n", ret);
    print_separator();

    // Test 8: Espacios múltiples
    printf("Test 8 - Múltiples argumentos:\n");
    char *echo_8[] = {"echo", "a", "b", "c", "d", "e", NULL};
    printf("Expected: a b c d e\\n\nActual:   ");
    ret = builtin_echo(echo_8);
    printf("Return value: %d\n", ret);
    print_separator();

    // Test 9: -n con mayúsculas (no debe funcionar)
    printf("Test 9 - Flag -N (mayúscula, no debe funcionar):\n");
    char *echo_9[] = {"echo", "-N", "test", NULL};
    printf("Expected: -N test\\n\nActual:   ");
    ret = builtin_echo(echo_9);
    printf("Return value: %d\n", ret);
    print_separator();

    // Test 10: Mezcla de flags válidas e inválidas
    printf("Test 10 - Flags: -n -nnn -na test:\n");
    char *echo_10[] = {"echo", "-n", "-nnn", "-na", "test", NULL};
    printf("Expected: -na test (sin \\n, -n y -nnn son válidas, -na rompe)\\n\nActual:   ");
    ret = builtin_echo(echo_10);
    printf("\nReturn value: %d\n", ret);
    print_separator();
}

void test_pwd(t_shell *mini)
{
    print_test_header("PWD");
    
    // Test 1: PWD normal
    printf("Test 1 - PWD normal:\n");
    char *expected = getcwd(NULL, 0);
    printf("Expected: %s\n", expected);
    printf("Actual:   ");
    int ret = builtin_pwd(mini);
    printf("Return value: %d\n", ret);
    if (ret == 0)
        printf("%sOK%s\n", COLOR_GREEN, COLOR_RESET);
    else
        printf("%sERROR: Debería retornar 0%s\n", COLOR_RED, COLOR_RESET);
    free(expected);
    print_separator();

    // Test 2: PWD cuando mini->pwd está corrupto
    printf("Test 2 - PWD con mini->pwd = NULL:\n");
    char *backup_pwd = mini->pwd;
    mini->pwd = NULL;
    printf("Expected: Debería usar getcwd() o buscar en env\nActual:   ");
    ret = builtin_pwd(mini);
    printf("Return value: %d\n", ret);
    mini->pwd = backup_pwd;
    print_separator();

    // Test 3: Comparar con mini->pwd
    printf("Test 3 - Verificar que coincide con mini->pwd:\n");
    printf("mini->pwd: %s\n", mini->pwd);
    printf("getcwd:    ");
    char *current = getcwd(NULL, 0);
    printf("%s\n", current);
    if (strcmp(mini->pwd, current) == 0)
        printf("%sOK: Coinciden%s\n", COLOR_GREEN, COLOR_RESET);
    else
        printf("%sWARNING: No coinciden%s\n", COLOR_YELLOW, COLOR_RESET);
    free(current);
    print_separator();
}

void test_env(t_shell *mini)
{
    print_test_header("ENV");
    
    // Test 1: Env normal
    printf("Test 1 - Env normal (primeros 5):\n");
    print_n_env(mini->env_list, 5);
    print_separator();

    // Test 2: Llamar a builtin_env sin argumentos
    printf("Test 2 - builtin_env(NULL, mini):\n");
    int ret = builtin_env(NULL, mini);
    printf("Return value: %d\n", ret);
    if (ret == 0)
        printf("%sOK%s\n", COLOR_GREEN, COLOR_RESET);
    else
        printf("%sERROR: Debería retornar 0%s\n", COLOR_RED, COLOR_RESET);
    print_separator();

    // Test 3: Añadir variable con valor
    printf("Test 3 - Añadir variable TEST_VAR=test_value:\n");
    t_env *node_with_value = malloc(sizeof(t_env));
    node_with_value->key = ft_strdup("TEST_VAR");
    node_with_value->value = ft_strdup("test_value");
    node_with_value->next = NULL;
    add_back_env(&mini->env_list, node_with_value);
    
    if (env_contains(mini->env_list, "TEST_VAR"))
        printf("%sOK: Variable añadida%s\n", COLOR_GREEN, COLOR_RESET);
    else
        printf("%sERROR: Variable no encontrada%s\n", COLOR_RED, COLOR_RESET);
    
    printf("\nVerificar que aparece en env:\n");
    char *value = get_env_value(mini->env_list, "TEST_VAR");
    printf("TEST_VAR=%s\n", value ? value : "(null)");
    print_separator();

    // Test 4: Variable sin valor (no debe aparecer en env)
    printf("Test 4 - Añadir VARIABLE_VACIA (sin valor):\n");
    t_env *node_empty = malloc(sizeof(t_env));
    node_empty->key = ft_strdup("VARIABLE_VACIA");
    node_empty->value = NULL;
    node_empty->next = NULL;
    add_back_env(&mini->env_list, node_empty);
    
    printf("Ejecutando builtin_env:\n");
    printf("(VARIABLE_VACIA NO debe aparecer porque value=NULL)\n");
    ret = builtin_env(NULL, mini);
    print_separator();

    // Test 5: Env con argumentos (debe dar error)
    printf("Test 5 - Env con argumentos (debe fallar):\n");
    char *env_err[] = {"env", "argumento_invalido", NULL};
    ret = builtin_env(env_err, mini);
    printf("Return value: %d\n", ret);
    if (ret != 0)
        printf("%sOK: Retornó error como esperado%s\n", COLOR_GREEN, COLOR_RESET);
    else
        printf("%sERROR: Debería retornar error%s\n", COLOR_RED, COLOR_RESET);
    print_separator();

    // Test 6: Verificar variables importantes
    printf("Test 6 - Verificar variables importantes del entorno:\n");
    char *important_vars[] = {"PATH", "HOME", "USER", "PWD", NULL};
    int i = 0;
    while (important_vars[i])
    {
        value = get_env_value(mini->env_list, important_vars[i]);
        printf("%s=%s\n", important_vars[i], value ? value : "(no encontrada)");
        i++;
    }
    print_separator();
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    
    t_shell mini;
    
    // Inicialización
    printf("%s\n╔════════════════════════════════════════╗\n", COLOR_BLUE);
    printf("║   MINISHELL BUILTIN TESTER v1.0      ║\n");
    printf("║   (echo, pwd, env)                    ║\n");
    printf("╚════════════════════════════════════════╝%s\n", COLOR_RESET);
    
    mini.env_list = init_env(envp);
    mini.pwd = getcwd(NULL, 0);
    mini.oldpwd = NULL;
    mini.exit_status = 0;

    if (!mini.env_list || !mini.pwd)
    {
        printf("%sERROR: Fallo en inicialización%s\n", COLOR_RED, COLOR_RESET);
        return (1);
    }

    printf("\n%sInformación inicial:%s\n", COLOR_YELLOW, COLOR_RESET);
    printf("PWD inicial: %s\n", mini.pwd);
    printf("Variables de entorno: ");
    int count = 0;
    t_env *tmp = mini.env_list;
    while (tmp)
    {
        count++;
        tmp = tmp->next;
    }
    printf("%d\n", count);

    // Ejecutar tests
    test_echo();
    test_pwd(&mini);
    test_env(&mini);

    // Resumen final
    printf("\n%s╔════════════════════════════════════════╗\n", COLOR_GREEN);
    printf("║        TESTS COMPLETADOS              ║\n");
    printf("╚════════════════════════════════════════╝%s\n", COLOR_RESET);
    
    printf("\n%sRevisa los resultados arriba.%s\n", COLOR_YELLOW, COLOR_RESET);
    printf("%sSi hay errores en rojo, corrige esos builtins.%s\n\n", COLOR_YELLOW, COLOR_RESET);

    // Limpieza básica
    free(mini.pwd);
    // free_env_list(mini.env_list); // Descomenta si tienes esta función
    
    return (0);
}
