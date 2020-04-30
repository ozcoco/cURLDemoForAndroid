package org.oz.demo.ui.main;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.lifecycle.ViewModelProvider;

import org.oz.demo.databinding.MainFragmentBinding;

public class MainFragment extends Fragment {

    private MainFragmentBinding mBinding;

    public static MainFragment newInstance() {
        return new MainFragment();
    }

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container,
                             @Nullable Bundle savedInstanceState) {

        mBinding = MainFragmentBinding.inflate(inflater, container, false);

        mBinding.setLifecycleOwner(this);

        mBinding.setVm(new ViewModelProvider(this).get(MainViewModel.class));

        return mBinding.getRoot();
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        if (mBinding != null)
            mBinding.unbind();
    }
}
