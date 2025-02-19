import dash
import dash_bootstrap_components as dbc
from dash import dcc, html, callback_context
from dash.dependencies import Input, Output, State
import plotly.graph_objs as go
import pandas as pd
import numpy as np
import math
import warnings
import ccxt
import logging
"""
EL SOFTWARE SE PROPORCIONA «TAL CUAL», SIN GARANTÍA DE NINGÚN TIPO, EXPRESA O
IMPLÍCITA, INCLUIDAS, ENTRE OTRAS, LAS GARANTÍAS DE COMERCIABILIDAD
IDONEIDAD PARA UN FIN DETERMINADO Y NO INFRACCIÓN. EN NINGÚN CASO
AUTORES NI LOS TITULARES DE LOS DERECHOS DE AUTOR SERÁN RESPONSABLES DE NINGUNA RECLAMACIÓN
RESPONSABILIDAD, YA SEA CONTRACTUAL, EXTRACONTRACTUAL O DE OTRO TIPO, DERIVADA DE,
DE O EN CONEXIÓN CON EL SOFTWARE O EL USO U OTRAS OPERACIONES CON EL
SOFTWARE.
"""
"""Este programa es su completa responsabilidad, cuide sus llaves API, el programa actual solo tendrá conexión con los servidores de Bitso, nadie se hará responsable de un mal uso ni es una recomendación de inversión, Bitso Internacional no creó, no revisó ni aprueba este programa, mismo hecho únicamente con fines educativos.\nUtilice este programa con cautela."""
# IMPORTAMOS pandas_ta ÚNICAMENTE PARA RSI, MFI, EMA, ETC.
# Si lo deseas, puedes quitarlo y hacer tus propios cálculos
import pandas_ta as pta

warnings.filterwarnings('ignore')
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)

external_stylesheets = [
    dbc.themes.CYBORG,
    "https://cdn.jsdelivr.net/npm/bootstrap-icons@1.10.5/font/bootstrap-icons.css"
]
app = dash.Dash(__name__, external_stylesheets=external_stylesheets)
server = app.server

# --------------------------------------------------------------------
# CONFIGURACIÓN BOT
# --------------------------------------------------------------------
modo_simulacion = True
exchange_ccxt = ccxt.bitso({
   #'apiKey': 'TU_API_KEY',
   #'secret': 'TU_SECRET_KEY',
    'enableRateLimit': True
})

saldo_money = 1000.0
saldo_monedas = 0.0
status = ''
ultimo_precio = 1.0
sma_20_anterior = 1.0
precio_anterior = 1.0
precision = 5

# Trackers globales
last_buy_price = None
wins = 0
draws = 0
losses = 0

df_simulacion = pd.DataFrame([])
df_order = pd.DataFrame([])
ultimo_procesado = 0

# --------------------------------------------------------------------
# IMPLEMENTACIÓN DE INDICADORES "A MANO" (SIN freqtrade / ni talib)
# --------------------------------------------------------------------

def typical_price(df):
    """
    Cálculo de Typical Price = (High + Low + Close) / 3.
    """
    return (df['High'] + df['Low'] + df['Close']) / 3.0

def bollinger_bands(series, window=20, stds=2):
    """
    Bollinger Bands manual (lower, mid, upper).
    """
    mid = series.rolling(window).mean()
    stdev = series.rolling(window).std()
    upper = mid + stds * stdev
    lower = mid - stds * stdev
    df_bb = pd.DataFrame({
        'bb_lowerband': lower,
        'bb_middleband': mid,
        'bb_upperband': upper
    })
    return df_bb

def chopiness(df, window=14):
    """
    Cálculo del Chopiness Index (CHOP) simplificado:
    CHOP(n) = 100 * [log10( sum(High-Low, n) / (max(High, n) - min(Low, n)) )] / log10(n)
    """
    high_low = (df['High'] - df['Low']).rolling(window).sum()
    highest = df['High'].rolling(window).max()
    lowest = df['Low'].rolling(window).min()
    rangema = highest - lowest
    chop = 100.0 * np.log10((high_low) / (rangema + 1e-9)) / np.log10(window)
    return chop

# --------------------------------------------------------------------
# PARÁMETROS DE NOSTALGIAFORINFINITY
# --------------------------------------------------------------------
NFI_PARAMS = {
    # 21 condiciones de compra con flags
    "buy_condition_1_enable": True,
    "buy_condition_2_enable": True,
    "buy_condition_3_enable": True,
    "buy_condition_4_enable": True,
    "buy_condition_5_enable": True,
    "buy_condition_6_enable": True,
    "buy_condition_7_enable": True,
    "buy_condition_8_enable": True,
    "buy_condition_9_enable": True,
    "buy_condition_10_enable": True,
    "buy_condition_11_enable": True,
    "buy_condition_12_enable": True,
    "buy_condition_13_enable": True,
    "buy_condition_14_enable": True,
    "buy_condition_15_enable": True,
    "buy_condition_16_enable": True,
    "buy_condition_17_enable": True,
    "buy_condition_18_enable": True,
    "buy_condition_19_enable": True,
    "buy_condition_20_enable": True,
    "buy_condition_21_enable": True,

    # 8 condiciones de venta
    "sell_condition_1_enable": True,
    "sell_condition_2_enable": True,
    "sell_condition_3_enable": True,
    "sell_condition_4_enable": True,
    "sell_condition_5_enable": True,
    "sell_condition_6_enable": True,
    "sell_condition_7_enable": True,
    "sell_condition_8_enable": True,

    # Offsets
    "ewo_low": -8.5,
    "ewo_high": 4.3,
    "low_offset_sma": 0.955,
    "low_offset_ema": 0.929,
    "low_offset_trima": 0.949,
    "low_offset_t3": 0.975,
    "low_offset_kama": 0.972,
    "high_offset_ema": 1.047,
    "buy_rsi_18": 26,
    "buy_chop_min_19": 58.2,
    "buy_rsi_1h_min_19": 65.3,
    "buy_rsi_15": 30,
    "buy_mfi_1": 26.0,
    "buy_rsi_1": 36.0,
    "buy_mfi_9": 30.0,
    "buy_mfi_11": 38.0,
    "sell_rsi_bb_2": 81.0,
    "sell_rsi_main_3": 82.0,
    "sell_dual_rsi_rsi_4": 73.4,
    "sell_dual_rsi_rsi_1h_4": 79.6,
    "sell_ema_relative_5": 0.024,
    "sell_rsi_under_6": 79.0,
    "sell_rsi_1h_7": 81.7,
    "sell_bb_relative_8": 1.1
}

# --------------------------------------------------------------------
# PARÁMETROS DE SUPERTREND
# --------------------------------------------------------------------
SUPERTREND_PARAMS = {
    "buy_m1": 4,
    "buy_p1": 8,
    "buy_m2": 7,
    "buy_p2": 9,
    "buy_m3": 1,
    "buy_p3": 8,
    "sell_m1": 1,
    "sell_p1": 16,
    "sell_m2": 3,
    "sell_p2": 18,
    "sell_m3": 6,
    "sell_p3": 18,
}

# --------------------------------------------------------------------
# Funciones de Ayuda
# --------------------------------------------------------------------
def truncate(number, decimals=0):
    if decimals == 0:
        return math.trunc(number)
    factor = 10.0 ** decimals
    return math.trunc(number * factor) / factor

def reset_vars():
    global saldo_money, saldo_monedas, status
    global df_simulacion, df_order, ultimo_procesado
    global ultimo_precio, sma_20_anterior, precio_anterior
    global last_buy_price, wins, draws, losses

    saldo_money = 1000.0
    saldo_monedas = 0.0
    status = ''
    df_simulacion = pd.DataFrame([])
    df_order = pd.DataFrame([])
    ultimo_procesado = 0
    ultimo_precio = 1.0
    sma_20_anterior = 1.0
    precio_anterior = 1.0
    last_buy_price = None
    wins = 0
    draws = 0
    losses = 0

def ejecutar_compra(token, cantidad, precio, fecha):
    global saldo_money, saldo_monedas, status, df_simulacion, ultimo_precio, last_buy_price
    if modo_simulacion:
        saldo_money -= cantidad * precio
        saldo_monedas += cantidad
        status = 'compra'
        ultimo_precio = precio
        last_buy_price = precio
        nueva = {'Date': fecha, 'Close': precio, 'Ultimo_Status': status, 'Ultimo_Precio': precio}
        df_simulacion = pd.concat([df_simulacion, pd.DataFrame([nueva])], ignore_index=True)
    else:
        try:
            order = exchange_ccxt.create_limit_buy_order(token, cantidad, precio)
            logger.info(f"Orden de compra real => {order}")
        except Exception as e:
            logger.error(f"Error compra real: {e}")

def ejecutar_venta(token, cantidad, precio, fecha):
    global saldo_money, saldo_monedas, status, df_simulacion, ultimo_precio
    global wins, draws, losses, last_buy_price
    if modo_simulacion:
        saldo_money += cantidad * precio
        saldo_monedas -= cantidad
        status = 'venta'
        ultimo_precio = precio
        if last_buy_price is not None:
            if precio > last_buy_price:
                wins += 1
            elif precio == last_buy_price:
                draws += 1
            else:
                losses += 1
        nueva = {'Date': fecha, 'Close': precio, 'Ultimo_Status': status, 'Ultimo_Precio': precio}
        df_simulacion = pd.concat([df_simulacion, pd.DataFrame([nueva])], ignore_index=True)
    else:
        try:
            order = exchange_ccxt.create_limit_sell_order(token, cantidad, precio)
            logger.info(f"Orden de venta real => {order}")
        except Exception as e:
            logger.error(f"Error venta real: {e}")


# --------------------------------------------------------------------
# FUNCIÓN SUPERTREND (SIN `talib` NI `pta.tr`)
# --------------------------------------------------------------------
def supertrend(df: pd.DataFrame, multiplier: float, period: int):
    """
    Implementación manual de supertrend, sin recurrir a talib ni freqtrade.
    1) Calculamos True Range manualmente:
         TR[i] = max(High[i]-Low[i], |High[i]-Close[i-1]|, |Low[i]-Close[i-1]| )
    2) ATR simple con rolling(period).mean()
    3) Basic/Final UB y LB
    4) ST y STX ('up'/'down')
    """
    df_calc = df.copy()

    # previous close
    df_calc['prev_close'] = df_calc['Close'].shift(1)

    # True Range manual
    def calc_tr(row):
        hl = row['High'] - row['Low']
        hc = abs(row['High'] - row['prev_close'])
        lc = abs(row['Low'] - row['prev_close'])
        return max(hl, hc, lc)

    df_calc['TR'] = df_calc.apply(calc_tr, axis=1)

    # ATR (rolling mean)
    df_calc['ATR'] = df_calc['TR'].rolling(period).mean()

    st = f"ST_{period}_{multiplier}"
    stx = f"STX_{period}_{multiplier}"

    # Basic upper / lower bands
    df_calc['basic_ub'] = (df_calc['High'] + df_calc['Low']) / 2.0 + multiplier * df_calc['ATR']
    df_calc['basic_lb'] = (df_calc['High'] + df_calc['Low']) / 2.0 - multiplier * df_calc['ATR']

    # Final UB y LB
    final_ub = [np.nan]*len(df_calc)
    final_lb = [np.nan]*len(df_calc)

    for i in range(len(df_calc)):
        if i < period:
            continue
        if i == period:
            final_ub[i] = df_calc['basic_ub'][i]
            final_lb[i] = df_calc['basic_lb'][i]
        else:
            # UB
            if (df_calc['basic_ub'][i] < final_ub[i-1]) or (df_calc['Close'][i-1] > final_ub[i-1]):
                final_ub[i] = df_calc['basic_ub'][i]
            else:
                final_ub[i] = final_ub[i-1]
            # LB
            if (df_calc['basic_lb'][i] > final_lb[i-1]) or (df_calc['Close'][i-1] < final_lb[i-1]):
                final_lb[i] = df_calc['basic_lb'][i]
            else:
                final_lb[i] = final_lb[i-1]

    df_calc['final_ub'] = final_ub
    df_calc['final_lb'] = final_lb

    # Supertrend
    st_list = [np.nan]*len(df_calc)
    for i in range(len(df_calc)):
        if i < period:
            continue
        if i == period:
            if df_calc['Close'][i] <= df_calc['final_ub'][i]:
                st_list[i] = df_calc['final_ub'][i]
            else:
                st_list[i] = df_calc['final_lb'][i]
        else:
            if st_list[i-1] == df_calc['final_ub'][i-1] and df_calc['Close'][i] <= df_calc['final_ub'][i]:
                st_list[i] = df_calc['final_ub'][i]
            elif st_list[i-1] == df_calc['final_ub'][i-1] and df_calc['Close'][i] > df_calc['final_ub'][i]:
                st_list[i] = df_calc['final_lb'][i]
            elif st_list[i-1] == df_calc['final_lb'][i-1] and df_calc['Close'][i] >= df_calc['final_lb'][i]:
                st_list[i] = df_calc['final_lb'][i]
            elif st_list[i-1] == df_calc['final_lb'][i-1] and df_calc['Close'][i] < df_calc['final_lb'][i]:
                st_list[i] = df_calc['final_ub'][i]

    df_calc[st] = st_list

    # STX => 'up' o 'down'
    stx_list = [np.nan]*len(df_calc)
    for i in range(len(df_calc)):
        if i < period:
            continue
        # si ST > 0 => definimos up/down
        if pd.notna(df_calc[st][i]):
            if df_calc['Close'][i] < df_calc[st][i]:
                stx_list[i] = 'down'
            else:
                stx_list[i] = 'up'

    df_calc[stx] = stx_list

    # Retornamos DataFrame con ST y STX
    return pd.DataFrame({
        'ST': df_calc[st],
        'STX': df_calc[stx]
    }, index=df_calc.index)


# --------------------------------------------------------------------
# CARGAR VELAS E INDICADORES
# --------------------------------------------------------------------
def cargar_ordenes(token, limit_candles):
    global df_order
    try:
        ohlcv = exchange_ccxt.fetch_ohlcv(symbol=token, timeframe='1h', limit=limit_candles)
    except Exception as e:
        logger.error(f"Error al obtener OHLCV: {e}")
        return
    
    df_temp = pd.DataFrame(ohlcv, columns=['OpenTime','Open','High','Low','Close','Volume'])
    df_temp['Date'] = pd.to_datetime(df_temp['OpenTime'], unit='ms')
    df_temp.sort_values('Date', inplace=True)
    df_temp.reset_index(drop=True, inplace=True)

    df_temp['Open'] = df_temp['Open'].astype(float)
    df_temp['High'] = df_temp['High'].astype(float)
    df_temp['Low']  = df_temp['Low'].astype(float)
    df_temp['Close'] = df_temp['Close'].astype(float)
    df_temp['Volume'] = df_temp['Volume'].astype(float)

    # Indicadores "Original"
    df_temp['SMA_20'] = df_temp['Close'].rolling(20).mean()
    df_temp['Minimo'] = df_temp['Close'].cummin()
    df_temp['Maximo'] = df_temp['Close'].cummax()

    # ---------- Indicadores NostalgiaForInfinity (usando pandas_ta) -------------
    df_temp['ema_20']  = df_temp.ta.ema(length=20, close='Close')
    df_temp['ema_200'] = df_temp.ta.ema(length=200, close='Close')
    df_temp['sma_20_nfi'] = df_temp.ta.sma(length=20, close='Close')
    df_temp['trima_20']   = df_temp.ta.trima(length=20, close='Close')
    df_temp['t3_20']      = df_temp.ta.t3(length=20, close='Close')
    df_temp['kama_20']    = df_temp.ta.kama(length=20, close='Close')

    df_temp['rsi'] = df_temp.ta.rsi(length=14, close='Close')
    df_temp['mfi'] = df_temp.ta.mfi(length=14)

    # EWO
    df_temp['ema_5']  = df_temp.ta.ema(length=5, close='Close')
    df_temp['ema_35'] = df_temp.ta.ema(length=35, close='Close')
    df_temp['ewo'] = (df_temp['ema_5'] - df_temp['ema_35']) / df_temp['Close'] * 100

    # Bollinger Bands manual
    tp = typical_price(df_temp)
    bb = bollinger_bands(tp, window=20, stds=2)
    df_temp['bb_lowerband']  = bb['bb_lowerband']
    df_temp['bb_middleband'] = bb['bb_middleband']
    df_temp['bb_upperband']  = bb['bb_upperband']

    # Chopiness manual
    df_temp['chop'] = chopiness(df_temp, window=14)

    # ---------- Cálculo Supertrend (3 para Buy, 3 para Sell) -------------
    st_params = SUPERTREND_PARAMS

    # 3 "buy"
    stx_b1 = supertrend(df_temp, multiplier=st_params["buy_m1"], period=st_params["buy_p1"])
    stx_b2 = supertrend(df_temp, multiplier=st_params["buy_m2"], period=st_params["buy_p2"])
    stx_b3 = supertrend(df_temp, multiplier=st_params["buy_m3"], period=st_params["buy_p3"])
    df_temp['stx_buy1'] = stx_b1['STX']
    df_temp['stx_buy2'] = stx_b2['STX']
    df_temp['stx_buy3'] = stx_b3['STX']

    # 3 "sell"
    stx_s1 = supertrend(df_temp, multiplier=st_params["sell_m1"], period=st_params["sell_p1"])
    stx_s2 = supertrend(df_temp, multiplier=st_params["sell_m2"], period=st_params["sell_p2"])
    stx_s3 = supertrend(df_temp, multiplier=st_params["sell_m3"], period=st_params["sell_p3"])
    df_temp['stx_sell1'] = stx_s1['STX']
    df_temp['stx_sell2'] = stx_s2['STX']
    df_temp['stx_sell3'] = stx_s3['STX']

    df_order = df_temp.copy()

# --------------------------------------------------------------------
# ACTUALIZAR LA ÚLTIMA VELA
# --------------------------------------------------------------------
def actualizar_datos(token):
    global df_order
    if df_order.empty:
        return

    try:
        ohlcv = exchange_ccxt.fetch_ohlcv(symbol=token, timeframe='1h', limit=1)
    except Exception as e:
        logger.error(f"Error al obtener la vela más reciente: {e}")
        return
    if not ohlcv:
        return

    nueva = ohlcv[0]
    fecha = pd.to_datetime(nueva[0], unit='ms')
    close = float(nueva[4])
    if fecha in df_order['Date'].values:
        return

    # Clonamos la última fila
    last_row = df_order.iloc[-1].copy()
    new_row = last_row.to_dict()
    new_row['Date']   = fecha
    new_row['Open']   = float(nueva[1])
    new_row['High']   = float(nueva[2])
    new_row['Low']    = float(nueva[3])
    new_row['Close']  = close
    new_row['Volume'] = float(nueva[5])
    new_row['Minimo'] = min(last_row['Minimo'], close)
    new_row['Maximo'] = max(last_row['Maximo'], close)

    # Ojo: No recalculamos supertrend en la última vela en "tiempo real"
    # si quisieras recalcular, deberías llamar de nuevo a supertrend() con todo el DF.
    df_order = pd.concat([df_order, pd.DataFrame([new_row])], ignore_index=True)

# --------------------------------------------------------------------
# ESTRATEGIA ORIGINAL
# --------------------------------------------------------------------
def simular_trading_original(token):
    global saldo_money, saldo_monedas, status
    global sma_20_anterior, precio_anterior, ultimo_procesado
    global wins, draws, losses, last_buy_price, ultimo_precio

    if df_order.empty:
        return

    for idx, row in df_order.iloc[ultimo_procesado:].iterrows():
        fecha = row['Date']
        precio = row['Close']
        minimo = row['Minimo']
        maximo = row['Maximo']
        sma_20 = row['SMA_20'] if not pd.isna(row['SMA_20']) else precio
        media = (minimo + maximo) / 2
        baja = (maximo / minimo > 1.1) and (precio / media < 0.965)

        if (status == '' or status == 'venta') and saldo_money > 0:
            cond_compra = (
                (not baja and precio < (minimo + media) / 2) or
                (baja and (precio / minimo < 1.05) and (precio > precio_anterior) and (sma_20 > sma_20_anterior))
            )
            if cond_compra:
                cant = truncate((saldo_money / precio) * 0.99, precision)
                ejecutar_compra(token, cant, precio, fecha)

        elif status == 'compra' and saldo_monedas > 0:
            cond_venta = (
                (not baja and (precio > media) and (sma_20 / sma_20_anterior > 1.002) and (precio / precio_anterior > 1.002))
                or
                (baja and (precio / ultimo_precio > 1.01))
            )
            if cond_venta:
                cant = truncate(saldo_monedas, precision)
                ejecutar_venta(token, cant, precio, fecha)

        sma_20_anterior = sma_20
        precio_anterior = precio
        ultimo_procesado = idx + 1

    if saldo_monedas > 0:
        ejecutar_venta(token, truncate(saldo_monedas, precision), ultimo_precio, fecha)

# --------------------------------------------------------------------
# ESTRATEGIA NFI
# --------------------------------------------------------------------
def simular_trading_nfi(token):
    global saldo_money, saldo_monedas, status
    global ultimo_procesado, ultimo_precio, last_buy_price
    global wins, draws, losses

    if df_order.empty:
        return

    p = NFI_PARAMS

    for idx, row in df_order.iloc[ultimo_procesado:].iterrows():
        fecha = row['Date']
        close = row['Close']
        volume = row['Volume']
        rsi = row['rsi'] if not pd.isna(row['rsi']) else 50
        mfi = row['mfi'] if not pd.isna(row['mfi']) else 50
        ewo = row['ewo'] if not pd.isna(row['ewo']) else 0

        # MAs
        ema_20 = row['ema_20'] if not pd.isna(row['ema_20']) else close
        sma_20nfi = row['sma_20_nfi'] if not pd.isna(row['sma_20_nfi']) else close
        trima_20 = row['trima_20'] if not pd.isna(row['trima_20']) else close
        t3_20    = row['t3_20'] if not pd.isna(row['t3_20']) else close
        kama_20  = row['kama_20'] if not pd.isna(row['kama_20']) else close

        # Offsets buy
        ema_offset_buy   = ema_20   * p['low_offset_ema']
        sma_offset_buy   = sma_20nfi* p['low_offset_sma']
        trima_offset_buy = trima_20 * p['low_offset_trima']
        t3_offset_buy    = t3_20    * p['low_offset_t3']
        kama_offset_buy  = kama_20  * p['low_offset_kama']

        # Reunimos las 21 conds de compra
        buy_conds = []

        # 1
        if p["buy_condition_1_enable"]:
            c1 = (
                (close < ema_offset_buy) &
                (mfi < 27) &
                (close < ema_20) &
                ((ewo < p["ewo_low"]) | (ewo > p["ewo_high"])) &
                (volume > 0)
            )
            buy_conds.append(c1)

        # 2
        if p["buy_condition_2_enable"]:
            c2 = (
                (close < sma_offset_buy) &
                (mfi < 30) &
                (close < ema_20) &
                ((ewo < p["ewo_low"]) | (ewo > p["ewo_high"])) &
                (volume > 0)
            )
            buy_conds.append(c2)

        # 3
        if p["buy_condition_3_enable"]:
            c3 = (
                (row['bb_lowerband'] < close) &
                (mfi < 35) &
                (trima_20 > 0) &
                ((ewo < p["ewo_low"]) | (ewo > p["ewo_high"]))
            )
            buy_conds.append(c3)

        # 4
        if p["buy_condition_4_enable"]:
            c4 = (
                (close < t3_offset_buy) &
                (rsi < 40) &
                (mfi < 35) &
                (volume > 0)
            )
            buy_conds.append(c4)

        # 5
        if p["buy_condition_5_enable"]:
            c5 = (
                (close < kama_offset_buy) &
                (rsi < p["buy_rsi_1"]) &
                (mfi < p["buy_mfi_1"]) &
                (volume > 0)
            )
            buy_conds.append(c5)

        # 6
        if p["buy_condition_6_enable"]:
            c6 = (
                (close < ema_offset_buy) &
                (mfi < 49) &
                (volume > 0)
            )
            buy_conds.append(c6)

        # 7
        if p["buy_condition_7_enable"]:
            c7 = (
                (close < trima_offset_buy) &
                (rsi < 35) &
                (volume > 0)
            )
            buy_conds.append(c7)

        # 8
        if p["buy_condition_8_enable"]:
            c8 = (
                (close < t3_offset_buy) &
                (rsi < 36) &
                (row['chop'] < 60) &
                (volume > 0)
            )
            buy_conds.append(c8)

        # 9
        if p["buy_condition_9_enable"]:
            c9 = (
                (close < sma_offset_buy) &
                (mfi < p["buy_mfi_9"]) &
                (volume > 0)
            )
            buy_conds.append(c9)

        # 10
        if p["buy_condition_10_enable"]:
            c10 = (
                (close < ema_offset_buy) &
                (rsi < 35) &
                (volume > 0)
            )
            buy_conds.append(c10)

        # 11
        if p["buy_condition_11_enable"]:
            c11 = (
                (close < sma_offset_buy) &
                (mfi < p["buy_mfi_11"]) &
                (volume > 0)
            )
            buy_conds.append(c11)

        # 12
        if p["buy_condition_12_enable"]:
            c12 = (
                (close < ema_offset_buy) &
                (ewo > 2) &
                (volume > 0)
            )
            buy_conds.append(c12)

        # 13
        if p["buy_condition_13_enable"]:
            c13 = (
                (close < sma_offset_buy) &
                (ewo < -7) &
                (volume > 0)
            )
            buy_conds.append(c13)

        # 14
        if p["buy_condition_14_enable"]:
            c14 = (
                (close < ema_offset_buy) &
                (close < sma_offset_buy) &
                (rsi < 40) &
                (volume > 0)
            )
            buy_conds.append(c14)

        # 15
        if p["buy_condition_15_enable"]:
            c15 = (
                (close < ema_offset_buy) &
                (rsi < p["buy_rsi_15"]) &
                (volume > 0)
            )
            buy_conds.append(c15)

        # 16
        if p["buy_condition_16_enable"]:
            c16 = (
                (close < ema_offset_buy) &
                (ewo > p["ewo_low"]) &
                (volume > 0)
            )
            buy_conds.append(c16)

        # 17
        if p["buy_condition_17_enable"]:
            c17 = (
                (close < sma_offset_buy) &
                (ewo < -10) &
                (volume > 0)
            )
            buy_conds.append(c17)

        # 18
        if p["buy_condition_18_enable"]:
            c18 = (
                (close < ema_offset_buy) &
                (rsi < p["buy_rsi_18"]) &
                (volume > 0)
            )
            buy_conds.append(c18)

        # 19
        if p["buy_condition_19_enable"]:
            c19 = (
                (row['chop'] < p["buy_chop_min_19"]) &
                (rsi < p["buy_rsi_1h_min_19"])
            )
            buy_conds.append(c19)

        # 20
        if p["buy_condition_20_enable"]:
            c20 = (
                (close < ema_offset_buy) &
                (rsi < 26) &
                (volume > 0)
            )
            buy_conds.append(c20)

        # 21
        if p["buy_condition_21_enable"]:
            c21 = (
                (close < sma_offset_buy) &
                (rsi < 23) &
                (volume > 0)
            )
            buy_conds.append(c21)

        buy_signal = any(
            bc.iloc[idx] if isinstance(bc, pd.Series) else bc
            for bc in buy_conds
        )

        # COMPRA
        if (status == '' or status == 'venta') and saldo_money > 0:
            if buy_signal:
                cant = truncate((saldo_money / close) * 0.99, precision)
                ejecutar_compra(token, cant, close, fecha)

        # SELL (8 condiciones)
        if status == 'compra' and saldo_monedas > 0:
            sell_conds = []

            if p["sell_condition_1_enable"]:
                sc1 = (
                    (close > (ema_20 * p["high_offset_ema"])) &
                    (volume > 0)
                )
                sell_conds.append(sc1)

            if p["sell_condition_2_enable"]:
                sc2 = (rsi > p["sell_rsi_bb_2"])
                sell_conds.append(sc2)

            if p["sell_condition_3_enable"]:
                sc3 = (rsi > p["sell_rsi_main_3"])
                sell_conds.append(sc3)

            if p["sell_condition_4_enable"]:
                sc4 = (
                    (rsi > p["sell_dual_rsi_rsi_4"]) &
                    (rsi > (p["sell_dual_rsi_rsi_1h_4"] - 5))
                )
                sell_conds.append(sc4)

            if p["sell_condition_5_enable"]:
                sc5 = (
                    (close > (ema_20 + (ema_20 * p["sell_ema_relative_5"]))) &
                    (rsi > 50)
                )
                sell_conds.append(sc5)

            if p["sell_condition_6_enable"]:
                sc6 = (rsi > p["sell_rsi_under_6"])
                sell_conds.append(sc6)

            if p["sell_condition_7_enable"]:
                sc7 = (rsi > p["sell_rsi_1h_7"])
                sell_conds.append(sc7)

            if p["sell_condition_8_enable"]:
                sc8 = (
                    (close > (row['bb_upperband'] * p["sell_bb_relative_8"])) &
                    (volume > 0)
                )
                sell_conds.append(sc8)

            sell_signal = any(
                sc.iloc[idx] if isinstance(sc, pd.Series) else sc
                for sc in sell_conds
            )

            if sell_signal:
                ejecutar_venta(token, truncate(saldo_monedas, precision), close, fecha)

        ultimo_procesado = idx + 1

    if saldo_monedas > 0:
        ejecutar_venta(token, truncate(saldo_monedas, precision), ultimo_precio, fecha)

# --------------------------------------------------------------------
# ESTRATEGIA SUPERTREND
# --------------------------------------------------------------------
def simular_trading_supertrend(token):
    global saldo_money, saldo_monedas, status
    global ultimo_procesado, ultimo_precio, last_buy_price
    global wins, draws, losses

    if df_order.empty:
        return

    for idx, row in df_order.iloc[ultimo_procesado:].iterrows():
        fecha = row['Date']
        close = row['Close']
        volume = row['Volume']

        stx_buy1 = row['stx_buy1']
        stx_buy2 = row['stx_buy2']
        stx_buy3 = row['stx_buy3']
        stx_sell1 = row['stx_sell1']
        stx_sell2 = row['stx_sell2']
        stx_sell3 = row['stx_sell3']

        # 3 "up" => buy
        buy_signal = (
            (stx_buy1 == 'up') and
            (stx_buy2 == 'up') and
            (stx_buy3 == 'up') and
            (volume > 0)
        )
        # 3 "down" => sell
        sell_signal = (
            (stx_sell1 == 'down') and
            (stx_sell2 == 'down') and
            (stx_sell3 == 'down') and
            (volume > 0)
        )

        if (status == '' or status == 'venta') and saldo_money > 0:
            if buy_signal:
                cant = truncate((saldo_money / close) * 0.99, precision)
                ejecutar_compra(token, cant, close, fecha)

        elif status == 'compra' and saldo_monedas > 0:
            if sell_signal:
                ejecutar_venta(token, truncate(saldo_monedas, precision), close, fecha)

        ultimo_procesado = idx + 1

    if saldo_monedas > 0:
        ejecutar_venta(token, truncate(saldo_monedas, precision), ultimo_precio, fecha)

# --------------------------------------------------------------------
# ACTUALIZAR GRÁFICO
# --------------------------------------------------------------------
def actualizar_grafico(token):
    df_graf = df_simulacion.copy()
    if not df_graf.empty:
        df_graf['Buy_Signal'] = np.where(df_graf['Ultimo_Status'] == 'compra', df_graf['Ultimo_Precio'], np.nan)
        df_graf['Sell_Signal'] = np.where(df_graf['Ultimo_Status'] == 'venta', df_graf['Ultimo_Precio'], np.nan)
    else:
        df_graf = pd.DataFrame(columns=['Date','Buy_Signal','Sell_Signal','Close'])
    
    df_data = df_order.copy()
    df_data['Buy_Signal'] = np.nan
    df_data['Sell_Signal'] = np.nan
    
    df_comb = pd.concat([df_data, df_graf], ignore_index=True)
    df_comb.sort_values('Date', inplace=True)
    df_comb.set_index('Date', inplace=True)
    
    fig = go.Figure()
    if 'Close' in df_comb.columns:
        fig.add_trace(go.Scatter(x=df_comb.index, y=df_comb['Close'],
                                 mode='lines', name='Close'))
    if 'Buy_Signal' in df_comb.columns:
        fig.add_trace(go.Scatter(x=df_comb.index, y=df_comb['Buy_Signal'],
                                 mode='markers', 
                                 marker=dict(color='green', symbol='triangle-up', size=10),
                                 name='Compra'))
    if 'Sell_Signal' in df_comb.columns:
        fig.add_trace(go.Scatter(x=df_comb.index, y=df_comb['Sell_Signal'],
                                 mode='markers', 
                                 marker=dict(color='red', symbol='triangle-down', size=10),
                                 name='Venta'))
    
    fig.update_layout(title=f"Trading Bot ccxt - {token}",
                      template='plotly_dark', height=600)
    
    saldo_final = saldo_money + saldo_monedas * ultimo_precio
    fig.add_annotation(x=0.98, y=0.95, xref='paper', yref='paper',
                       text=f"SALDO FINAL: {saldo_final:,.2f}", showarrow=False,
                       font=dict(size=14, color='white'), align='right')
    fig.add_annotation(x=0.98, y=0.90, xref='paper', yref='paper',
                       text=f"MONEDAS: {saldo_monedas:,.5f}", showarrow=False,
                       font=dict(size=14, color='white'), align='right')
    return fig

# --------------------------------------------------------------------
# LAYOUT DE DASH
# --------------------------------------------------------------------
navbar = dbc.Navbar(
    dbc.Container([
        dbc.NavbarBrand("Bot ccxt (Bitso)", className="ms-2", style={'fontSize': 24})
    ]),
    color="dark", dark=True
)

def obtener_tokens_ccxt():
    exchange_ccxt.load_markets()
    all_markets = list(exchange_ccxt.markets.keys())
    tokens_filtrados = [m for m in all_markets if m.endswith('/MXN') or m.endswith('/USD')]
    tokens_filtrados.sort()
    return tokens_filtrados

tokens_disponibles = obtener_tokens_ccxt()

app.layout = dbc.Container([
    navbar,
    html.Br(),
    dbc.Row([
        dbc.Col([
            dbc.Card([
                dbc.CardBody([
                    html.H5("Configuración Inicial", className="card-title"),
                    
                    # Selección Token
                    dbc.Row([
                        dbc.Col([
                            html.Label("Token:"),
                            dcc.Dropdown(
                                id='dropdown-token',
                                options=[{'label': t, 'value': t} for t in tokens_disponibles],
                                value='BTC/MXN',
                                clearable=False
                            )
                        ], width=12)
                    ], className="mb-3"),
                    
                    # Límite de velas
                    dbc.Row([
                        dbc.Col([
                            html.Label("Límite de Velas (ccxt):"),
                            dbc.Input(id='input-limit', type='number', value=500, min=1, step=1)
                        ], width=12)
                    ], className="mb-3"),
                    
                    # Estrategia
                    dbc.Row([
                        dbc.Col([
                            html.Label("Estrategia:"),
                            dcc.Dropdown(
                                id='dropdown-estrategia',
                                options=[
                                    {'label': 'Original', 'value': 'original'},
                                    {'label': 'NFI (21 BUY / 8 SELL)', 'value': 'nfi'},
                                    {'label': 'Supertrend (3 up => Buy / 3 down => Sell)', 'value': 'supertrend'},
                                ],
                                value='original',
                                clearable=False
                            )
                        ], width=12)
                    ], className="mb-3"),
                    
                    dbc.Button("Aplicar Configuración", id='btn-aplicar',
                               color='primary', className="w-100")
                ])
            ])
        ], width=3),
        dbc.Col([
            dcc.Graph(id='grafico-ccxt', style={'height':'70vh'})
        ], width=9)
    ]),
    html.Br(),
    dbc.Row([
        dbc.Col([
            dbc.Card([
                dbc.CardBody([
                    html.H5(["Saldo ", html.I(className="bi bi-wallet2")], className="card-title"),
                    html.P(id='saldo-ccxt', className="card-text", children="1000.0")
                ])
            ], className="mb-3")
        ], width=2),
        dbc.Col([
            dbc.Card([
                dbc.CardBody([
                    html.H5(["Monedas ", html.I(className="bi bi-coin")], className="card-title"),
                    html.P(id='monedas-ccxt', className="card-text", children="0.0")
                ])
            ], className="mb-3")
        ], width=2),
        dbc.Col([
            dbc.Card([
                dbc.CardBody([
                    html.H5(["Estado ", html.I(className="bi bi-activity")], className="card-title"),
                    html.P(id='estado-ccxt', className="card-text", children="Inicial")
                ])
            ], className="mb-3")
        ], width=2),
        dbc.Col([], width=6)
    ]),
    dbc.Row([
        dbc.Col([
            dbc.Card([
                dbc.CardBody([
                    html.H5(["Victorias ", html.I(className="bi bi-trophy")], className="card-title"),
                    html.P(id='wins-ccxt', className="card-text", children="0")
                ])
            ], className="mb-3")
        ], width=2),
        dbc.Col([
            dbc.Card([
                dbc.CardBody([
                    html.H5(["Empates ", html.I(className="bi bi-hand-thumbs-up")], className="card-title"),
                    html.P(id='draws-ccxt', className="card-text", children="0")
                ])
            ], className="mb-3")
        ], width=2),
        dbc.Col([
            dbc.Card([
                dbc.CardBody([
                    html.H5(["Derrotas ", html.I(className="bi bi-emoji-frown")], className="card-title"),
                    html.P(id='losses-ccxt', className="card-text", children="0")
                ])
            ], className="mb-3")
        ], width=2),
        dbc.Col([], width=6)
    ]),
    dcc.Interval(id='interval-ccxt', interval=3600*1000, n_intervals=0)
], fluid=True)

# --------------------------------------------------------------------
# CALLBACK
# --------------------------------------------------------------------
@app.callback(
    Output('grafico-ccxt','figure'),
    Output('saldo-ccxt','children'),
    Output('monedas-ccxt','children'),
    Output('estado-ccxt','children'),
    Output('wins-ccxt','children'),
    Output('draws-ccxt','children'),
    Output('losses-ccxt','children'),
    [Input('interval-ccxt','n_intervals'),
     Input('btn-aplicar','n_clicks')],
    [State('dropdown-token','value'),
     State('input-limit','value'),
     State('dropdown-estrategia','value')]
)
def actualizar_dashboard_ccxt(n_intervals, n_clicks, token, limit_candles, estrategia):
    trigger_id = callback_context.triggered[0]['prop_id'].split('.')[0]
    global saldo_money, saldo_monedas, status, precio_anterior, ultimo_precio
    
    if trigger_id == 'btn-aplicar' and n_clicks:
        reset_vars()
        precio_anterior = 1.0
        ultimo_precio = 1.0
        cargar_ordenes(token, limit_candles)

        if estrategia == 'original':
            simular_trading_original(token)
        elif estrategia == 'nfi':
            simular_trading_nfi(token)
        elif estrategia == 'supertrend':
            simular_trading_supertrend(token)

    elif trigger_id == 'interval-ccxt' and n_intervals > 0:
        actualizar_datos(token)
        if estrategia == 'original':
            simular_trading_original(token)
        elif estrategia == 'nfi':
            simular_trading_nfi(token)
        elif estrategia == 'supertrend':
            simular_trading_supertrend(token)

    fig = actualizar_grafico(token)
    estado_text = status.capitalize() if status else "Inicial"
    return (
        fig,
        f"{saldo_money:,.2f}",
        f"{saldo_monedas:,.5f}",
        estado_text,
        str(wins),
        str(draws),
        str(losses)
    )

# --------------------------------------------------------------------
# MAIN
# --------------------------------------------------------------------
if __name__ == '__main__':
    app.run_server(debug=True)