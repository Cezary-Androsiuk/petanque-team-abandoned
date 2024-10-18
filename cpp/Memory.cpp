#include "Memory.h"

Memory::Memory(QObject *parent)
    : QObject{parent}
{

#if DELETE_MEMORY_AT_START
    D("removed memory file at start with status: " + BOOL_TO_STR(QFile::remove(MEMORY_FILE)));
#endif

}

void Memory::load()
{
    emit this->memoryLoaded();
}

void Memory::save()
{
    if(!QFileInfo::exists( MEMORY_DIR ))
    {
        if(!QDir().mkdir( MEMORY_DIR ))
        {
            E("Failed to create directory: " MEMORY_DIR );
        }
    }

    QFile file( MEMORY_FILE );
    if(!file.open(QIODevice::OpenModeFlag::WriteOnly))
    {
        QString message = "Failed to create memory file: " + file.errorString();
        E(message);
        emit this->memoryError(message);
        return;
    }
    file.close();

    emit this->memorySaved();
}

bool Memory::memoryFileExist() const
{
    return QFileInfo::exists( MEMORY_FILE );
}
