package org.oz.curl;

import java.nio.ByteBuffer;

/**
 * @ProjectName: cURL-demo
 * @Package: org.oz.curl
 * @ClassName: Test
 * @Description:
 * @Author: oz
 * @CreateDate: 2020/4/29 15:23
 * @UpdateUser:
 * @UpdateDate: 2020/4/29 15:23
 * @UpdateRemark:
 * @Version: 1.0
 */
public class Test {

    public interface Callback {

        default void onWrite(ByteBuffer buf) {
        }

        default void onHeader(ByteBuffer buf) {
        }
    }

    private Callback callback;

    private ByteBuffer data;
    private ByteBuffer header;

    public Test(Callback callback) {
        
        Runtime.getRuntime().loadLibrary("net-lib");

        data = ByteBuffer.allocateDirect(1024 * 32);

        header = ByteBuffer.allocateDirect(1024 * 32);

        this.callback = callback;

        native_init();

    }

    public void test() {
        native_test();
    }

    @Override
    protected void finalize() throws Throwable {
        super.finalize();

        native_destroy();
        data.clear();
        header.clear();

    }

    private void onWriteCallback(ByteBuffer buf) {

        if (callback != null)
            callback.onWrite(buf);
    }

    private void onHeaderCallback(ByteBuffer buf) {

        if (callback != null)
            callback.onHeader(buf);
    }

    private native void native_init();

    private native void native_test();

    private native void native_destroy();
}
