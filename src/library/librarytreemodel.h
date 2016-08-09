#ifndef LIBRARYTREEMODEL_H
#define LIBRARYTREEMODEL_H

#include <QHash>
#include <QPixmap>
#include <QSqlQuery>
#include <QStringList>

#include "library/treeitemmodel.h"
#include "preferences/usersettings.h"

class CoverInfo;
class LibraryFeature;
class TrackCollection;

const QString LIBRARYTREEMODEL_SORT = "LibraryTree_Sort"; // ConfigValue key for Library Tree Model sort

class LibraryTreeModel : public TreeItemModel {
    Q_OBJECT
  public:
    LibraryTreeModel(LibraryFeature* pFeature, 
                     TrackCollection* pTrackCollection, 
                     UserSettingsPointer pConfig,
                     QObject* parent = nullptr);

    virtual QVariant data(const QModelIndex &index, int role) const;
    
    void setSortOrder(QStringList sortOrder);
    QStringList getSortOrder();
    void setFolderRecursive(bool recursive);
    bool getFolderRecursive();
    
  public slots:  
    void reloadTracksTree();
    
  private:
    
    struct CoverIndex {
        int iCoverHash;
        int iCoverLoc;
        int iTrackLoc;
        int iCoverSrc;
        int iCoverType;
    };
    
  private slots:
    void coverFound(const QObject* requestor, int requestReference, const CoverInfo&,
                    QPixmap pixmap, bool fromCache);
    
  private:    
    QVariant getQuery(TreeItem* pTree) const;
    void createTracksTree();
    void createFoldersTree();
    void addCoverArt(const CoverIndex& index, const QSqlQuery& query, TreeItem* pTree);
    void createTreeFromSource(const QString& dir, QSqlQuery& query);
    
    LibraryFeature* m_pFeature;
    TrackCollection* m_pTrackCollection;
    UserSettingsPointer m_pConfig;
    
    QStringList m_sortOrder;
    QStringList m_coverQuery;
    
    TreeItem* m_pLibraryItem;
    TreeItem* m_pFoldersRoot;    
    
    bool m_folderRecursive;
};

#endif // LIBRARYTREEMODEL_H
