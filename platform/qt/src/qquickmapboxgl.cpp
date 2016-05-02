#include "qquickmapboxglrenderer.hpp"

#include <QQuickMapboxGL>

#include <QQuickItem>
#include <QtGlobal>

QQuickMapboxGL::QQuickMapboxGL(QQuickItem *parent_)
    : QQuickFramebufferObject(parent_)
{
#if QT_VERSION >= 0x050600
    // FIXME: https://github.com/mapbox/mapbox-gl-native/issues/4866
    setMirrorVertically(true);
#endif
}

QQuickMapboxGL::~QQuickMapboxGL()
{
}

QQuickFramebufferObject::Renderer *QQuickMapboxGL::createRenderer() const
{
    return new QQuickMapboxGLRenderer();
}

void QQuickMapboxGL::setMinimumZoomLevel(qreal zoom)
{
    zoom = qMax(0., zoom);
    zoom = qMin(m_maximumZoomLevel, zoom);

    if (m_minimumZoomLevel == zoom) {
        return;
    }

    m_minimumZoomLevel = zoom;

    emit minimumZoomLevelChanged();
}

qreal QQuickMapboxGL::minimumZoomLevel() const
{
    return m_minimumZoomLevel;
}

void QQuickMapboxGL::setMaximumZoomLevel(qreal zoom)
{
    zoom = qMin(20., zoom);
    zoom = qMax(m_minimumZoomLevel, zoom);

    if (m_maximumZoomLevel == zoom) {
        return;
    }

    m_maximumZoomLevel = zoom;

    emit maximumZoomLevelChanged();
}

qreal QQuickMapboxGL::maximumZoomLevel() const
{
    return m_maximumZoomLevel;
}

void QQuickMapboxGL::setZoomLevel(qreal zoom)
{
    zoom = qMin(m_maximumZoomLevel, zoom);
    zoom = qMax(m_minimumZoomLevel, zoom);

    if (m_zoomLevel == zoom) {
        return;
    }

    m_zoomLevel = zoom;

    m_syncState |= ZoomNeedsSync;
    update();

    emit zoomLevelChanged(m_zoomLevel);
}

qreal QQuickMapboxGL::zoomLevel() const
{
    return m_zoomLevel;
}

void QQuickMapboxGL::setCenter(const QGeoCoordinate &coordinate)
{
    if (m_center == coordinate) {
        return;
    }

    m_center = coordinate;

    m_syncState |= CenterNeedsSync;
    update();

    emit centerChanged(m_center);
}

QGeoCoordinate QQuickMapboxGL::center() const
{
    return m_center;
}


void QQuickMapboxGL::setVisibleRegion(const QGeoShape &shape)
{
    m_visibleRegion = shape;
}

QGeoShape QQuickMapboxGL::visibleRegion() const
{
    return m_visibleRegion;
}

int QQuickMapboxGL::swapSyncState()
{
    int oldState = m_syncState;

    m_syncState = NothingNeedsSync;

    return oldState;
}
