package com.oit.utils;

import android.content.Context;
import android.util.SparseArray;
import android.view.View;
import android.widget.TextView;

/**
 * Created by john
 * time: 2017-03-28
 * desc: ${TODO}
 */

public class DialogViewHolder {
    private final SparseArray<View> mViews;
    private View mDialogView;
    public Context mContext;
    private DialogViewHolder(Context context, int layoutId) {
        this.mContext = context;
        this.mViews = new SparseArray<>();
        mDialogView = View.inflate(context, layoutId, null);
    }

    public static DialogViewHolder get(Context context, int layoutId) {
        return new DialogViewHolder(context, layoutId);
    }

    public View getConvertView() {
        return mDialogView;
    }

    /**
     * Set the string for TextView
     *
     * @param viewId
     * @param text
     * @return
     */
    public DialogViewHolder setText(int viewId, CharSequence text) {
        TextView view = getView(viewId);
        view.setText(text);
        return this;
    }

    public DialogViewHolder setTextLong(int viewId, int content) {
        TextView view = getView(viewId);
        view.setText(content);
        return this;
    }

    /**
     * set view visible
     *
     * @param viewId
     * @return
     */
    public DialogViewHolder setViewInViSible(int viewId) {
        View view = getView(viewId);
        view.setVisibility(View.INVISIBLE);
        return this;
    }

    /**
     * set view visible
     *
     * @param viewId
     * @return
     */
    public DialogViewHolder setViewViSible(int viewId) {
        View view = getView(viewId);
        view.setVisibility(View.VISIBLE);
        return this;
    }

    /**
     * set view gone
     *
     * @param viewId
     * @return
     */
    public DialogViewHolder setViewGone(int viewId) {
        View view = getView(viewId);
        view.setVisibility(View.GONE);
        return this;
    }

    /**
     * 设置点击
     */
    public DialogViewHolder setOnClick(int viewId, View.OnClickListener onClick) {
        View view = getView(viewId);
        view.setOnClickListener(onClick);
        return this;
    }

    /**
     * Through control the Id of the access to control, if not join views
     *
     * @param viewId
     * @return
     */

    @SuppressWarnings("unchecked")
    public <T extends View> T getView(int viewId) {
        View view = mViews.get(viewId);
        if (view == null) {
            view = mDialogView.findViewById(viewId);
            mViews.put(viewId, view);
        }
        return (T) view;
    }
}
