#ifndef DEFINITIONS_H
#define DEFINITIONS_H

//! @brief Volume structure to encapsulate viewing volumes such as viewport.
struct Volume
{
    //! @brief Method to set structure.
    void Set( double _left, double _right, double _bottom, double _top, double _near, double _far )
    {
        left = _left;
        right = _right;
        bottom = _bottom;
        top = _top;
        near = _near;
        far = _far;
    }

    //! @brief Method to get structure Volume, by components.
    void Get( double* _left, double* _right, double* _bottom, double* _top, double* _near, double* _far )
    {
        if( _left != NULL ) *_left = left;
        if( _right != NULL ) *_right = right;
        if( _bottom != NULL ) *_bottom = bottom;
        if( _top != NULL ) *_top = top;
        if( _near != NULL ) *_near = near;
        if( _far != NULL ) *_far = far;
    }

    //! @brief Method to get structure as a whole.
    void Get( Volume& _volume )
    {
        _volume.left = left;
        _volume.right = right;
        _volume.bottom = bottom;
        _volume.top = top;
        _volume.near = near;
        _volume.far = far;
    }

    //! Left side of the volume.
    double left;
    //! Right side of the volume.
    double right;
    //! Bottom side of the volume.
    double bottom;
    //! Top side of the volume.
    double top;
    //! Near side of the volume.
    double near;
    //! Far side of the volume.
    double far;
};

#endif

