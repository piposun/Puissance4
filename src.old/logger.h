#ifndef HEADER_LOG
#define HEADER_LOG

/*! \file logger.h
    \brief Gestionnaire des logs dans le terminal.
    \version 0.1

    Permet l'affichage des logs dans le terminal et gere leur style en fonction de leur niveau.
*/

/*! \enum LEVEL_LOG
    \brief Permet la gestion des niveau de logs.
*/
typedef enum {
LEVEL_LOG_ERROR = -1, /**< Indique le niveau de log ERREUR */
LEVEL_LOG_INFO, /**< Indique le niveau de log INFO */
LEVEL_LOG_WARN, /**< Indique le niveau de log ALERTE */
LEVEL_LOG_DEBUG, /**< Indique le niveau de log DEBUG */
LEVEL_LOG_MENU /**< Indique le niveau de log MENU */
} LEVEL_LOG;

/*! \def COL_ERROR
    \brief Definition de la couleur Light Red pour l'affichage dans le terminal
*/
#define COL_ERROR "\x1B[31m";

/*! \def COL_INFO
    \brief Definition de la couleur White pour l'affichage dans le terminal
*/
#define COL_INFO  "\x1B[37m";

/*! \def COL_WARN
    \brief Definition de la couleur Yellow pour l'affichage dans le terminal
*/
#define COL_WARN  "\x1B[33m";

/*! \def COL_DEBUG
    \brief Definition de la couleur Light Blue pour l'affichage dans le terminal
*/
#define COL_DEBUG "\x1B[94m";

/*! \def COL_MENU
    \brief Definition de la couleur Green pour l'affichage dans le terminal
*/
#define COL_MENU "\x1B[32m";

/*! \def SIZE_HEADER
    \brief Taille de l'entete du message.
*/

#define SIZE_HEADER 10

/*! \def SIZE_MARGE
    \brief Marge pour eviter l'overflow.
*/
#define SIZE_MARGE  50

/*! \def DEBUG
    \brief Macro qui appel la fonction log_print avec le niveau LEVEL_LOG_DEBUG.
*/
#define DEBUG(format, ...) log_print(LEVEL_LOG_DEBUG, __LINE__, __FILE__, format, ##__VA_ARGS__)
/*! \def INFO
    \brief Macro qui appel la fonction log_print avec le niveau LEVEL_LOG_INFO.
*/
#define INFO(format, ...)  log_print(LEVEL_LOG_INFO, __LINE__, __FILE__, format, ##__VA_ARGS__)
/*! \def WARN
    \brief Macro qui appel la fonction log_print avec le niveau LEVEL_LOG_WARN.
*/
#define WARN(format, ...)  log_print(LEVEL_LOG_WARN, __LINE__, __FILE__, format, ##__VA_ARGS__)
/*! \def ERROR
    \brief Macro qui appel la fonction log_print avec le niveau LEVEL_LOG_ERROR.
*/
#define ERROR(format, ...) log_print(LEVEL_LOG_ERROR, __LINE__, __FILE__, format, ##__VA_ARGS__)
/*! \def MENU
    \brief Macro qui appel la fonction log_print avec le niveau LEVEL_LOG_MENU.
*/
#define MENU(format, ...) log_print(LEVEL_LOG_MENU, __LINE__, __FILE__, format, ##__VA_ARGS__)
/*! \fn void log_print(LEVEL_LOG level, int line, char *file, const char *format, ...)
    \brief Ecrit les logs dans le terminal en fonction de leur niveau.

    \param level Niveau du message.
    \param format Format du message.
    \param ... Liste d'arguments variable.
*/
void log_print(LEVEL_LOG level, int line, char *file, const char *format, ...);

#endif /* HEADER_LOG */
