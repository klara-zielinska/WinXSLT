#include "testtools.h"
#include "Utils/xsltutils.h"
#include <archive.h>
#include <archive_entry.h>
#include <QFile>
#include <QDir>
#include <QTemporaryFile>
#include <stdexcept>

void copy_data(archive* ar, archive* aw)
{
    la_ssize_t r;
    const void* buff;
    size_t size;
    la_int64_t offset;

    while (
        (r = archive_read_data_block(ar, &buff, &size, &offset)) != ARCHIVE_EOF)
    {
        if (r != ARCHIVE_OK && r != ARCHIVE_WARN)
            throw std::runtime_error(archive_error_string(ar));
        r = archive_write_data_block(aw, buff, size, offset);
        if (r != ARCHIVE_OK && r != ARCHIVE_WARN)
            throw std::runtime_error(archive_error_string(aw));
    }
}

//void untar(QFileDevice &source, const QDir &targetDir)
//{
//    archive* a;
//    archive* ext;
//    archive_entry* entry;
//    int r;
//    QString startDir = QDir::current().absolutePath();
//    QDir::setCurrent(targetDir.absolutePath());

//    a = archive_read_new();
//    ext = archive_write_disk_new();
//    archive_write_disk_set_options(ext, 0);
//    archive_read_support_format_tar(a);

//    source.open(QIODevice::ReadOnly);
//    auto h = source.handle();
//    r = archive_read_open_fd(a, h, 102400);
//    if (r != ARCHIVE_OK && r != ARCHIVE_WARN)
//    {
//        source.close();
//        QDir::setCurrent(startDir);
//        throw std::runtime_error(archive_error_string(a));
//    }
//    while ((r = archive_read_next_header(a, &entry)) != ARCHIVE_EOF)
//    {
//        if (r != ARCHIVE_OK && r != ARCHIVE_WARN)
//        {
//            source.close();
//            QDir::setCurrent(startDir);
//            throw std::runtime_error(archive_error_string(a));
//        }
//        r = archive_write_header(ext, entry);
//        if (r != ARCHIVE_OK && r != ARCHIVE_WARN)
//        {
//            source.close();
//            QDir::setCurrent(startDir);
//            throw std::runtime_error(archive_error_string(ext));
//        }
//        else
//        {
//            copy_data(a, ext);
//            r = archive_write_finish_entry(ext);
//            if (r != ARCHIVE_OK && r != ARCHIVE_WARN)
//            {
//                source.close();
//                QDir::setCurrent(startDir);
//                throw std::runtime_error(archive_error_string(ext));
//            }
//        }
//    }
//    archive_read_close(a);
//    archive_read_free(a);

//    archive_write_close(ext);
//    archive_write_free(ext);

//    source.close();

//    QDir::setCurrent(startDir);
//}

void copyIODevContent(QIODevice &source, QIODevice &dest)
{
    char buf[0x100000];
    qint64 res1, res2;

    if (!source.open(QIODevice::ReadOnly))
        throw std::runtime_error(source.errorString().toLatin1());
    if (!dest.open(QIODevice::WriteOnly))
        throw std::runtime_error(dest.errorString().toLatin1());

    do {
        res1 = source.read(buf, sizeof(buf));
        if (res1 == -1)
            throw std::runtime_error(source.errorString().toLatin1());
        res2 = dest.write(buf, res1);
        if (res2 == -1)
            throw std::runtime_error(dest.errorString().toLatin1());
        if (res2 < res1)
            throw std::runtime_error(
                    "Could not write a required number of bytes"
                    "into a temporary file");
    }
    while (res1 == sizeof(buf));

    dest.close();
    source.close();
}

bool qIODevEq(QIODevice &dev1, QIODevice &dev2)
{
    qint64 r1, r2, result;
    char buf1[1000000], buf2[1000000];

    if (!dev1.open(QIODevice::ReadOnly))
        throw std::runtime_error(dev1.errorString().toLatin1());
    if (!dev2.open(QIODevice::ReadOnly))
    {
        dev1.close();
        throw std::runtime_error(dev2.errorString().toLatin1());
    }

    if (dev1.size() != dev2.size())
        return false;

    result = true;
    while ((r1 = dev1.read(buf1, sizeof(buf1))) != 0)
    {
        if (r1 == -1)
        {
            dev1.close();
            dev2.close();
            throw std::runtime_error(dev1.errorString().toLatin1());
        }
        if ((r2 = dev2.read(buf2, sizeof(buf2))) == -1)
        {
            dev1.close();
            dev2.close();
            throw std::runtime_error(dev2.errorString().toLatin1());
        }
        Q_ASSERT(r1 == r2);
        if (memcmp(buf1, buf2, r1) != 0)
        {
            result = false;
            break;
        }
    }

    dev1.close();
    dev2.close();
    return result;
}

void copyDir(QDir source, QDir target)
{
    Q_ASSERT(source.exists());

    if (!target.exists())
        target.mkpath(target.absolutePath());

    foreach (QString name, source.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
        copyDir(QDir(source.filePath(name)), QDir(target.filePath(name)));

    foreach (QString name, source.entryList(QDir::Files))
        QFile::copy(source.filePath(name), target.filePath(name));
}

bool xmlSimpleNodesEq(xmlNodePtr node1, xmlNodePtr node2)
{
    if (node1 == node2) return true;
    if (node1 == nullptr || node2 == nullptr) return false;
    if (node1->type != node2->type) return false;

    if (node1->type == XML_TEXT_NODE)
        return
        QString::fromUtf8(XmlCString::of(xmlNodeGetContent(node1))).trimmed() ==
        QString::fromUtf8(XmlCString::of(xmlNodeGetContent(node2))).trimmed();

    if (node1->type == XML_ELEMENT_NODE)
    {
        if (QString::fromUtf8(XmlCString::of(node1->name)) !=
            QString::fromUtf8(XmlCString::of(node2->name)))
            return false;

        xmlAttr* attr1 = node1->properties;
        xmlAttr* attr2 = node2->properties;

        while (attr1 != nullptr && attr2 != nullptr)
        {
            xmlChar* value1 =
                    xmlNodeListGetString(node1->doc, attr1->children, 1);
            xmlChar* value2 =
                    xmlNodeListGetString(node2->doc, attr2->children, 1);
            bool valsEqual = QString::fromUtf8(XmlCString::of(value1)) ==
                             QString::fromUtf8(XmlCString::of(value2));
            xmlFree(value1);
            xmlFree(value2);

            if (!valsEqual ||
                QString::fromUtf8(XmlCString::of(attr1->name)) !=
                QString::fromUtf8(XmlCString::of(attr2->name)))
                return false;

            attr1 = attr1->next;
            attr2 = attr2->next;
        }

        if (attr1 || attr2)
            return false;
    }

    node1 = node1->children;
    node2 = node2->children;
    while (node1 != nullptr && node2 != nullptr)
        if (!xmlSimpleNodesEq(node1, node2))
            return false;
        else
        {
            node1 = node1->next;
            node2 = node2->next;
        }
    return node1 == nullptr && node2 == nullptr;
}
