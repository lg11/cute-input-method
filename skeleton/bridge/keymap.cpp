#include <qnamespace.h>
#include <iostream>

using namespace std ;

int main( int argc, char** argv ) {
    cout << "#ifndef KEYMAP_H\n" ;
    cout << "#define KEYMAP_H\n" ;
    cout << "\n" ;
    cout << "#include <gdk/gdkkeysyms.h>\n" ;
    cout << "\n" ;

    cout << "int convert_keycode( int keycode ) {\n" ;
    cout << "    switch ( keycode ) {\n" ;

    char num = '0' ;
    for ( int i = Qt::Key_0 ; i <= Qt::Key_9 ; i++ ) {
        cout << "    case GDK_KEY_" << num << " :\n" ;
        cout << "        return " << i << ";\n" ;
        num++ ;
    }

    char up = 'A' ;
    char down = 'a' ;
    for ( int i = Qt::Key_A ; i <= Qt::Key_Z ; i++ ) {
        cout << "    case GDK_KEY_" << up << " :\n" ;
        cout << "        return " << i << ";\n" ;
        cout << "    case GDK_KEY_" << down << " :\n" ;
        cout << "        return " << i << ";\n" ;
        up++ ; down++ ;
    }

    cout << "    case GDK_KEY_BackSpace :\n" ;
    cout << "        return " << Qt::Key_Backspace << ";\n" ;
    cout << "    case GDK_KEY_Return :\n" ;
    cout << "        return " << Qt::Key_Return << ";\n" ;
    cout << "    case GDK_KEY_space :\n" ;
    cout << "        return " << Qt::Key_Space << ";\n" ;
    cout << "    case GDK_KEY_minus :\n" ;
    cout << "        return " << Qt::Key_Minus << ";\n" ;
    cout << "    case GDK_KEY_equal :\n" ;
    cout << "        return " << Qt::Key_Equal << ";\n" ;
    cout << "    default :\n" ;
    cout << "        return -1 ;\n" ;
    cout << "    }\n" ;
    cout << "}\n" ;
    
    cout << "\n" ;
    cout << "int convert_modifiers( int modifiers ) {\n" ;
    cout << "    int flag = " << Qt::NoModifier << " ;\n" ;
    cout << "    if ( modifiers & GDK_SHIFT_MASK )\n" ;
    cout << "        flag |= " << Qt::ShiftModifier << " ;\n" ;
    cout << "    if ( modifiers & GDK_CONTROL_MASK )\n" ;
    cout << "        flag |= " << Qt::ControlModifier << " ;\n" ;
    cout << "    if ( modifiers & GDK_MOD1_MASK )\n" ;
    cout << "        flag |= " << Qt::AltModifier << " ;\n" ;
    cout << "    if ( modifiers & GDK_META_MASK )\n" ;
    cout << "        flag |= " << Qt::MetaModifier << " ;\n" ;
    cout << "    return flag ;\n" ;
    cout << "}\n" ;

    cout << "\n" ;
    cout << "#endif\n" ;

    return 0 ;
}
