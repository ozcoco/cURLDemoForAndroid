package org.oz.demo.ui.main;

import androidx.lifecycle.MutableLiveData;
import androidx.lifecycle.ViewModel;

import org.oz.curl.Test;

import java.nio.ByteBuffer;

public class MainViewModel extends ViewModel implements Test.Callback {

    public final static String TAG = MainViewModel.class.getCanonicalName();

    public MutableLiveData<String> msg = new MutableLiveData<>();

    private IMainModel model;

    @Override
    protected void onCleared() {
        super.onCleared();

        model = null;
    }

    public IMainModel getModel() {
        return model == null ? new MainModel() : model;
    }

    @Override
    public void onWrite(ByteBuffer buf) {

        String val = msg.getValue();

        if (val != null) {
            val = val.concat("\n--------------------------------------------------\n");
            val = val.concat(new String(buf.array()));
        } else {
            val = new String(buf.array());
        }

        msg.postValue(val);

    }

    @Override
    public void onHeader(ByteBuffer buf) {

        String val = msg.getValue();

        if (val != null) {
            val = val.concat("\n--------------------------------------------------\n");
            val = val.concat(new String(buf.array()));
        } else {
            val = new String(buf.array());
        }

        msg.postValue(val);

    }
}
