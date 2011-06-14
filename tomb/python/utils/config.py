import os

def check_path( path_list ) :
    result = ""
    for path in path_list :
        if os.path.exists( path ) :
            result = path
            break
    return result

#runtime_path = [ os.path.expanduser( "~/.config/cim/data/new_formated" ), "/opt/cim/data/new_formated", "../../data/new_formated", os.path.expanduser( "~/workspace/cim/" ) ]

sysdict_path = [ os.path.expanduser( "~/.config/cim/data/formated" ), "/opt/cim/data/formated", "../../data/formated", os.path.expanduser( "~/workspace/cim/data/formated" ) ]

qml_qwert_path = [ os.path.expanduser( "~/.config/cim/skeleton/qwert/qml" ), "/opt/cim/skeleton/qwert/qml", "./qml/qwert.qml" ]
