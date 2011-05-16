#include "utils.h"
#include "conn.h"
#include <hildon-input-method/hildon-im-plugin.h>


typedef struct{
    GtkWindow parent;
}him_plugin;

typedef struct{
    GtkWindowClass parent;
}him_plugin_class;

typedef struct{
    HildonIMUI* ui;
    dbus_conn* conn;
}him_plugin_private;

#define HIM_PLUGIN_TYPE (him_plugin_get_type())
#define HIM_PLUGIN( obj ) GTK_CHECK_CAST( obj, HIM_PLUGIN_TYPE, him_plugin )
#define HIM_PLUGIN_CLASS( klass ) GTK_CHECK_CLASS_CAST( klass, HIM_PLUGIN_TYPE, him_plugin_class )
#define HIM_PLUGIN_PRIVATE( obj ) G_TYPE_INSTANCE_GET_PRIVATE( obj, HIM_PLUGIN_TYPE, him_plugin_private )

static GType him_plugin_type = 0;
static GtkWidgetClass* parent_class = NULL;

static dbus_conn* conn;

static gint cursor_offset;
static gint surround_length;
static gboolean win_flag;

GType him_plugin_get_type(void){ return him_plugin_type; }

gboolean him_plugin_request_enter( GObject* plugin ){
    g_debug( "him_plugin_request_enter" ) ;
    him_plugin_private* priv = HIM_PLUGIN_PRIVATE( plugin ) ;
    hildon_im_ui_send_communication_message( priv->ui, HILDON_IM_CONTEXT_HANDLE_ENTER ) ;
    return TRUE ;
}

gboolean him_plugin_request_commit( GObject* plugin, GString gstr ){
    g_debug( "him_plugin_request_commit \"%s\"", gstr.str );
    him_plugin_private* priv = HIM_PLUGIN_PRIVATE( plugin );
    /*hildon_im_ui_send_utf8( priv->ui, gstr.str );*/

    if ( win_flag ){
        hildon_im_ui_send_surrounding_offset( priv->ui, TRUE, surround_length - cursor_offset );
        gint i;
        for( i = 0; i < surround_length; i++ ){
            hildon_im_ui_send_communication_message( priv->ui, HILDON_IM_CONTEXT_HANDLE_BACKSPACE );
        }
        hildon_im_ui_send_utf8( priv->ui, gstr.str );
    }
    else
        hildon_im_ui_send_surrounding_content( priv->ui, gstr.str );
    return TRUE;
}

static void enable( HildonIMPlugin* plugin, gboolean init ){
    g_debug( "enable" );
    him_plugin_private* priv = HIM_PLUGIN_PRIVATE( plugin );
    priv->conn = conn;
    dbus_conn_set_commit_func( priv->conn, (GObject*)plugin, him_plugin_request_commit );
    dbus_conn_set_enter_func( priv->conn, (GObject*)plugin, him_plugin_request_enter );
    /*hildon_im_ui_send_communication_message( priv->ui, HILDON_IM_CONTEXT_SURROUNDING_MODE );*/
    Window win = hildon_im_ui_get_input_window( priv->ui );
    win_flag = check_x11win_classhint(win);
    /*if ( win_flag )*/
        hildon_im_ui_send_communication_message( priv->ui, HILDON_IM_CONTEXT_REQUEST_SURROUNDING_FULL );
    /*else*/
        /*hildon_im_ui_send_communication_message( priv->ui, HILDON_IM_CONTEXT_REQUEST_SURROUNDING );*/


}

static void disable( HildonIMPlugin* plugin ){
    g_debug( "disable" );
}
static void settings_changed( HildonIMPlugin* plugin, const gchar* key, const GConfValue* value ){
    g_debug( "setting_changed" );
}
static void language_settings_changed( HildonIMPlugin* plugin, const gint index ){
    g_debug( "language_settings_changed" );
}
static void input_mode_changed( HildonIMPlugin* plugin ){
    g_debug( "input_mode_changed" );
}
static void keyboard_state_changed( HildonIMPlugin* plugin ){
    g_debug( "keyboard_state_changed" );
}
static void client_widget_changed( HildonIMPlugin* plugin ){
    g_debug( "client_widget_changed" );
}
static void character_autocase( HildonIMPlugin* plugin ){
    g_debug( "character_autocase" );
}
static void clear( HildonIMPlugin* plugin ){
    g_debug( "clear" );
}
static void save_data( HildonIMPlugin* plugin ){
    g_debug( "save_data" );
}
static void mode_a( HildonIMPlugin* plugin ){
    g_debug( "mode_a" );
}
static void mode_b( HildonIMPlugin* plugin ){
    g_debug( "mode_b" );
}
static void language( HildonIMPlugin* plugin ){
    g_debug( "language" );
}
static void backspace( HildonIMPlugin* plugin ){
    g_debug( "backspace" );
}
static void enter( HildonIMPlugin* plugin ){
    g_debug( "enter" );
}
static void tab( HildonIMPlugin* plugin ){
    g_debug( "tab" );
}
static void fullscreen( HildonIMPlugin* plugin, gboolean fullscreen ){
    g_debug( "fullscreen" );
}
static void select_region( HildonIMPlugin *plugin, gint start, gint end ){
    g_debug( "select_region" );
}

static void key_event( HildonIMPlugin *plugin, GdkEventType type, guint state, guint keyval, guint hardware_keycode ){
    g_debug( "key_event" );
}

static void transition( HildonIMPlugin *plugin, gboolean from ){
    g_debug( "transition" );
}
static void surrounding_received( HildonIMPlugin *plugin, const gchar *surrounding, gint offset ){
    g_debug( "surrounding_received %s", surrounding );
    him_plugin_private* priv = HIM_PLUGIN_PRIVATE( plugin );
    /*hildon_im_ui_send_communication_message( priv->ui, HILDON_IM_CONTEXT_HANDLE_BACKSPACE );*/
    cursor_offset = offset;
    surround_length = g_utf8_strlen( surrounding, -1 );
    g_debug( "him_plugin_surrounding_offset = %d, length = %d", offset, surround_length );
    dbus_call_pad_show( surrounding );
    /*hildon_im_ui_send_surrounding_content( priv->ui, "" );*/
}

static void button_activated( HildonIMPlugin *plugin, HildonIMButton button, gboolean long_press ){
    g_debug( "button_activated" );
}
static void preedit_committed( HildonIMPlugin *plugin, const gchar *committed_preedit ){
    g_debug( "preedit_committed" );
}

//ui interface function
static void get_property( GObject* object, guint prop_id, GValue* value, GParamSpec* pspec ){
    g_debug( "get_property" );
    him_plugin_private* priv;

    g_return_if_fail( HIM_PLUGIN(object) );
    priv = HIM_PLUGIN_PRIVATE(object);

    switch ( prop_id ){
        case HILDON_IM_PROP_UI:
            g_value_set_object( value, priv->ui );
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID( object, prop_id, pspec );
            break;
    }
}

static void set_property( GObject* object, guint prop_id, const GValue* value, GParamSpec* pspec ){
    g_debug( "set_property" );
    him_plugin_private* priv;

    g_return_if_fail( HIM_PLUGIN(object) );
    priv = HIM_PLUGIN_PRIVATE(object);

    switch ( prop_id ){
        case HILDON_IM_PROP_UI:
            priv->ui = g_value_get_object( value );
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID( object, prop_id, pspec );
            break;
    }
}
static void finalize( GObject *object ){
    g_debug( "finalize" );
    if ( G_OBJECT_CLASS( parent_class )->finalize )
        G_OBJECT_CLASS( parent_class )->finalize( object );
}
static void realize ( GtkWidget *widget ){
    g_debug( "realize" );
    g_return_if_fail( HIM_PLUGIN(widget) );
    GTK_WIDGET_SET_FLAGS( widget, GTK_REALIZED );
}

static gboolean destroy( GtkWidget* widget, GdkEventAny* event ){
    g_debug( "destroy" );
    //release priv resource in this place
    return FALSE;
}
static gboolean expose( GtkWidget* widget, GdkEventExpose* event ){
    g_debug( "expose" );
    //create priv resource in this place
    return TRUE;
}

static void him_plugin_class_init( him_plugin_class* klass ){
    g_debug( "him_plugin_class_init" );
    GObjectClass* object_class;
    GtkWidgetClass* widget_class;

    parent_class = g_type_class_peek_parent( klass );
    g_type_class_add_private( klass, sizeof(him_plugin_private) );

    object_class = G_OBJECT_CLASS( klass );
    widget_class = GTK_WIDGET_CLASS( klass );

    object_class->set_property = set_property;
    object_class->get_property = get_property;
    object_class->finalize = finalize;

    widget_class->realize = realize;
    widget_class->destroy_event = destroy;
    widget_class->expose_event = expose;

    g_object_class_install_property(object_class, HILDON_IM_PROP_UI,
            g_param_spec_object(HILDON_IM_PROP_UI_DESCRIPTION, 
                HILDON_IM_PROP_UI_DESCRIPTION,
                "maemo-chinese-input-pad-plugin",
                HILDON_IM_TYPE_UI,
                G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY
                )
            );
}

static void him_plugin_init( him_plugin* plugin ){
    g_debug( "him_plugin_init" );
}

GtkWidget* him_plugin_widget_new( HildonIMUI* widget ){
    g_debug( "him_plugin_widget_new" );
    return g_object_new( HIM_PLUGIN_TYPE, HILDON_IM_PROP_UI_DESCRIPTION, widget, NULL );
}

static void him_plugin_interface_init( HildonIMPluginIface* iface ){
    g_debug( "interface_init" );
    iface->enable = enable;
    iface->disable = disable;
    iface->settings_changed = settings_changed;
    iface->language_settings_changed = language_settings_changed;
    iface->input_mode_changed = input_mode_changed;
    iface->keyboard_state_changed = keyboard_state_changed;
    iface->client_widget_changed = client_widget_changed;
    iface->character_autocase = character_autocase;
    iface->clear = clear;
    iface->save_data = save_data;
    iface->mode_a = mode_a;
    iface->mode_b = mode_b;
    iface->language = language;
    iface->backspace = backspace;
    iface->enter = enter;
    iface->tab = tab;
    iface->fullscreen = fullscreen;
    iface->select_region = select_region;
    iface->key_event = key_event;
    iface->transition = transition;
    iface->surrounding_received = surrounding_received;
    iface->button_activated = button_activated;
    iface->preedit_committed = preedit_committed;
}

void module_init( GTypeModule* module ){
    g_debug( "module_init" );
    static const GTypeInfo type_info = {
        sizeof( him_plugin_class ),
        NULL, /* base_init */
        NULL, /* base_finalize */
        (GClassInitFunc) him_plugin_class_init,
        NULL, /* class_finalize */
        NULL, /* class_data */
        sizeof( him_plugin ),
        0, /* n_preallocs */
        (GInstanceInitFunc) him_plugin_init,
    };
    static const GInterfaceInfo him_plugin_info = {
        (GInterfaceInitFunc) him_plugin_interface_init,
        NULL, /* interface_finalize */
        NULL, /* interface_data */
    };
    him_plugin_type = g_type_module_register_type( module, GTK_TYPE_WIDGET, "him_plugin", &type_info, 0 );
    g_type_module_add_interface( module, HIM_PLUGIN_TYPE, HILDON_IM_TYPE_PLUGIN, &him_plugin_info );

    conn = dbus_conn_new();
    
    cursor_offset = 0;
    surround_length = 0;
}

void module_exit( void ){
    g_debug( "module_exit" );
}

HildonIMPlugin* module_create( HildonIMUI* widget ){
    g_debug( "module_create" );
    /*count_integer = 0;*/
    return HILDON_IM_PLUGIN( him_plugin_widget_new( widget ) );
}

const HildonIMPluginInfo* hildon_im_plugin_get_info( void ){
    g_debug( "hildon_im_him_plugin_get_info" );
    static const HildonIMPluginInfo info = 
    {
        "MAEMO-CHINESE-INPUT-PAD-PLUGIN",
        "maemo-chinese-input-pad-plugin",
        NULL,
        NULL,
        FALSE,
        FALSE,
        HILDON_IM_TYPE_SPECIAL_STANDALONE,
        HILDON_IM_GROUP_CUSTOM,
        HILDON_IM_DEFAULT_PLUGIN_PRIORITY,
        NULL,
        NULL,
        FALSE,
        HILDON_IM_DEFAULT_HEIGHT,
        HILDON_IM_TRIGGER_NONE
    };
    return &info;
}

gchar** hildon_im_plugin_get_available_languages( gboolean* free ){
    g_debug( "him_plugin_get_available_languages" );
    static gchar* list[] = { "zh_CN", "en_GB", "en_US", NULL };
    *free = FALSE;
    return list;
}

