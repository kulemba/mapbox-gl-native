package com.mapbox.mapboxsdk.annotations;

import com.mapbox.mapboxsdk.maps.MapboxMap;

/**
 * MarkerView is an annotation that shows an View at a geographical location.
 * <p>
 * This class uses {@link com.mapbox.mapboxsdk.maps.MapboxMap.MarkerViewAdapter} to adapt a
 * MarkerView model to an Android SDK {@link android.view.View} object.
 * </p>
 * <p>
 * An {@link InfoWindow} can be shown when a MarkerView is pressed
 * </p>
 */
public class MarkerView extends Marker {

    private MarkerViewManager markerViewManager;

    private float anchorU;
    private float anchorV;

    private float offsetX;
    private float offsetY;

    private float infoWindowAnchorU;
    private float infoWindowAnchorV;

    private boolean flat;
    private boolean visible = true;

    private int selectAnimRes;
    private int deselectAnimRes;

    private float tiltValue;
    private float rotation;
    private float alpha = 1;

    /**
     * Publicly hidden default constructor
     */
    MarkerView() {
    }

    /**
     * Creates a instance of MarkerView using the builder of MarkerView
     *
     * @param baseMarkerViewOptions the builder used to construct the MarkerView
     */
    public MarkerView(BaseMarkerViewOptions baseMarkerViewOptions) {
        super(baseMarkerViewOptions);
        this.anchorU = baseMarkerViewOptions.getAnchorU();
        this.anchorV = baseMarkerViewOptions.getAnchorV();
        this.infoWindowAnchorU = baseMarkerViewOptions.getInfoWindowAnchorU();
        this.infoWindowAnchorV = baseMarkerViewOptions.getInfoWindowAnchorV();
        this.flat = baseMarkerViewOptions.isFlat();
        this.selectAnimRes = baseMarkerViewOptions.getSelectAnimRes();
        this.deselectAnimRes = baseMarkerViewOptions.getDeselectAnimRes();
        this.infoWindowAnchorU = baseMarkerViewOptions.infoWindowAnchorU;
        this.infoWindowAnchorV = baseMarkerViewOptions.infoWindowAnchorV;
        this.anchorU = baseMarkerViewOptions.anchorU;
        this.anchorV = baseMarkerViewOptions.anchorV;
    }

    /**
     * Specifies the anchor being set on a particular point point of the MarkerView.
     * <p>
     * The anchor point is specified in the continuous space [0.0, 1.0] x [0.0, 1.0], where (0, 0)
     * is the top-left corner of the image, and (1, 1) is the bottom-right corner.
     * </p>
     *
     * @param u u-coordinate of the anchor, as a ratio of the image width (in the range [0, 1])
     * @param v v-coordinate of the anchor, as a ratio of the image height (in the range [0, 1])
     */
    public void setAnchor(float u, float v) {
        this.anchorU = u;
        this.anchorV = v;
    }

    /**
     * Get the horizontal distance, normalized to [0, 1], of the anchor from the left edge.
     *
     * @return the u-value of the anchor
     */
    public float getAnchorU() {
        return anchorU;
    }

    /**
     * Get the vertical distance, normalized to [0, 1], of the anchor from the top edge.
     *
     * @return the v-value of the anchor
     */
    public float getAnchorV() {
        return anchorV;
    }

    /**
     * Internal method to set the horizontal calculated offset.
     * <p>
     * These are calculated based on the View bounds and the provided anchor.
     * </p>
     *
     * @param x the x-value of the offset
     */
    void setOffsetX(float x) {
        offsetX = x;
    }

    /**
     * Internal method to set the vertical calculated offset.
     * <p>
     * These are calculated based on the View bounds and the provided anchor.
     * </p>
     *
     * @param y the y-value of the offset
     */
    void setOffsetY(float y) {
        offsetY = y;
    }

    /**
     * Internal method to get the horizontal calculated offset
     *
     * @return the calculated horizontal offset
     */
    float getOffsetX() {
        return offsetX;
    }

    /**
     * Internal method to get the vertical calculated offset
     *
     * @return the calculated vertical offset
     */
    float getOffsetY() {
        return offsetY;
    }

    /**
     * Specifies the anchor point of the info window on the View of the MarkerView.
     * <p>
     * This is specified in the same coordinate system as the anchor.
     * </p>
     * <p>
     * The default is the top middle of the View.
     * </p>
     *
     * @param u u-coordinate of the info window anchor, as a ratio of the image width (in the range [0, 1])
     * @param v v-coordinate of the info window anchor, as a ratio of the image height (in the range [0, 1])
     * @see #setAnchor(float, float) for more details.
     */
    public void setInfoWindowAnchor(float u, float v) {
        this.infoWindowAnchorU = u;
        this.infoWindowAnchorV = v;
    }

    /**
     * Get the horizontal distance, normalized to [0, 1], of the info window anchor from the left edge.
     *
     * @return the u value of the InfoWindow anchor.
     */
    public float getInfoWindowAnchorU() {
        return infoWindowAnchorU;
    }

    /**
     * Get the vertical distance, normalized to [0, 1], of the info window anchor from the top edge.
     *
     * @return the v value of the InfoWindow anchor.
     */
    public float getInfoWindowAnchorV() {
        return infoWindowAnchorV;
    }

    /**
     * Get the flat state of a MarkerView.
     *
     * @return true is the MarkerView is flat; false is the MarkerView is billboard
     */
    public boolean isFlat() {
        return flat;
    }

    /**
     * Sets whether this marker should be flat against the map true or a billboard facing the camera false.
     *
     * @param flat the flat state of the MarkerView
     */
    public void setFlat(boolean flat) {
        this.flat = flat;
    }

    /**
     * Get the animator resource used to animate to the selected state of a MarkerView.
     *
     * @return the animator resource used
     */
    public int getSelectAnimRes() {
        return selectAnimRes;
    }

    /**
     * Set the animator resource used to animate to the deselected state of a MarkerView.
     *
     * @param selectAnimRes the animator resource used
     */
    public void setSelectAnimRes(int selectAnimRes) {
        this.selectAnimRes = selectAnimRes;
    }

    /**
     * Get the animator resource used to animate to the deslected state of a MarkerView.
     *
     * @return the animator resource used
     */
    public int getDeselectAnimRes() {
        return deselectAnimRes;
    }

    /**
     * Set the animator resource used to animate to the selected state of a MarkerView.
     *
     * @param deselectAnimRes the animator resource used
     */
    public void setDeselectAnimRes(int deselectAnimRes) {
        this.deselectAnimRes = deselectAnimRes;
    }

    /**
     * Internal method to get the current tilted value of a MarkerView.
     *
     * @return the tilted value
     */
    float getTilt() {
        return tiltValue;
    }

    /**
     * Internal method to set the current titled value of a MarkerView.
     *
     * @param tiltValue the tilted value to set
     */
    void setTilt(float tiltValue) {
        this.tiltValue = tiltValue;
    }

    /**
     * Set the visible state of a MarkerView.
     *
     * @param visible true will make the MarkerView visible, false will hide the MarkerViews
     */
    public void setVisible(boolean visible) {
        this.visible = visible;
        if (markerViewManager != null) {
            markerViewManager.animateVisible(this, visible);
        }
    }

    /**
     * Returns the visible state of the MarkerView.
     *
     * @return the visible state
     */
    public boolean isVisible() {
        return visible;
    }

    /**
     * Set the rotation value of the MarkerView.
     * <p>
     * This will result in animating the rotation of the MarkerView using an rotation animator
     * from current value to the provided parameter value.
     * </p>
     *
     * @param rotation the rotation value to animate to
     */
    public void setRotation(float rotation) {
        this.rotation = rotation;
        if (markerViewManager != null) {
            markerViewManager.animateRotation(this, rotation);
        }
    }

    /**
     * Get the rotation value of the MarkerView.
     *
     * @return the rotation value
     */
    public float getRotation() {
        return rotation;
    }

    /**
     * Get the alpha value of the MarkerView.
     *
     * @return the alpha value
     */
    public float getAlpha() {
        return alpha;
    }

    /**
     * Set the alpha value of the MarkerView.
     * <p>
     * This will result in animating the alpha of the MarkerView using an alpha animator
     * from current value to the provided parameter value.
     * </p>
     *
     * @param alpha the alpha value to animate to
     */
    public void setAlpha(float alpha) {
        this.alpha = alpha;
        if (markerViewManager != null) {
            markerViewManager.animateAlpha(this, alpha);
        }
    }

    /**
     * Set the MapboxMap associated tot the MapView containing the MarkerView.
     * <p>
     * This method is used to instantiate the MarkerView and provide an instance of {@link com.mapbox.mapboxsdk.maps.MapboxMap.MarkerViewAdapter}
     * </p>
     *
     * @param mapboxMap the MapboxMap instances
     */
    @Override
    public void setMapboxMap(MapboxMap mapboxMap) {
        super.setMapboxMap(mapboxMap);
        markerViewManager = mapboxMap.getMarkerViewManager();
    }

    /**
     * Get the String representation of a MarkerView.
     *
     * @return the String representation
     */
    @Override
    public String toString() {
        return "MarkerView [position[" + getPosition() + "]]";
    }
}
