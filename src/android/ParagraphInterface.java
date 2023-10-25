/* Voxar Labs - CIn/UFPE, Recife, Brazil
*
* Copyright(c) 2017-2018 by Voxar Labs - CIn/UFPE
*
* This software is the confidential and proprietary information
* of Voxar Labs - Center of Informatics of the Federal University 
* of Pernambuco ("Confidential Information"). You
* shall not disclose such Confidential Information and shall use
* it only in accordance with the terms of the license agreement
* you entered into with Voxar Labs CIn/UFPE.
*
* Description: pARagraph technology.
*
* @author João Gabriel Santiago Mauricio de Abreu (jgsma@cin.ufpe.br),
*         João Marcelo Xavier Natário Teixeira (jmxnt@cin.ufpe.br),
*         Lucas Oliveira Maggi (lom@cin.ufpe.br),
*         Veronica Teichrieb (vt@cin.ufpe.br).
*
* @since 2017-04-07
*/
package voxar.paragraph;

import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaInterface;
import org.apache.cordova.CordovaPlugin;
import org.apache.cordova.LOG;
import org.apache.cordova.PluginResult;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import android.annotation.SuppressLint;
import android.app.AlertDialog;
import android.app.AlertDialog.Builder;
import android.app.ProgressDialog;
import android.content.DialogInterface;
import android.content.res.Resources;
import android.media.Ringtone;
import android.media.RingtoneManager;
import android.net.Uri;
import android.widget.EditText;
import android.widget.TextView;
import android.util.Log;
import android.content.Context;
import android.content.Intent;

import voxar.paragraph.Paragraph;


/**
 * This class provides an interface to Paragraph API.
 *
 * Be aware that this implementation gets called on 
 * navigator.paragraph.{init|open|retrieve}.
 */
public class ParagraphInterface extends CordovaPlugin {

    private static final String LOG_TAG = "ParagraphInterface";

    private Paragraph paragraph;

    /**
     * Constructor.
     */
    public ParagraphInterface() {
        paragraph = new Paragraph();
    }

    /**
     * Executes the request and returns PluginResult.
     *
     * @param action            The action to execute.
     * @param args              JSONArray of arguments for the plugin.
     * @param callbackContext   The callback context used when calling back into JavaScript.
     * @return                  True when the action was valid, false otherwise.
     */
    public boolean execute(String action, JSONArray args, CallbackContext callbackContext) throws JSONException {

    	if(this.cordova.getActivity().isFinishing()) return true;
    	if (action.equals("init")) {
            paragraph.Init(args.getString(0), this.cordova.getActivity().getApplicationContext());
            callbackContext.sendPluginResult(new PluginResult(PluginResult.Status.OK, 0));
        } else if (action.equals("open")) {
            boolean status = paragraph.Open(args.getString(0));
            callbackContext.sendPluginResult(new PluginResult(PluginResult.Status.OK, status));
        } else if (action.equals("retrieveFromPath")) {
            String documentID = "" + paragraph.RetrieveFromPath(args.getString(0));
            callbackContext.sendPluginResult(new PluginResult(PluginResult.Status.OK, documentID));
        }
        else {
            return false;
        }

        callbackContext.success();
        return true;
    }


}
