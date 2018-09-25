! function(e) { var t = { extend: function() { arguments[0] = arguments[0] || {}; for (var e = 1; e < arguments.length; e += 1)
                for (var i in arguments[e]) arguments[e].hasOwnProperty(i) && ("object" == typeof arguments[e][i] ? arguments[e][i] instanceof Array ? arguments[0][i] = arguments[e][i] : arguments[0][i] = t.extend(arguments[0][i], arguments[e][i]) : arguments[0][i] = arguments[e][i]); return arguments[0] } };

    function i(e) { this.options = t.extend({}, i.defaultOptions, e), this.clear() }

    function a(e) { this.options = t.extend({}, a.defaultChartOptions, e), this.seriesSet = [], this.currentValueRange = 1, this.currentVisMinValue = 0, this.lastRenderTimeMillis = 0 }
    i.defaultOptions = { resetBoundsInterval: 3e3, resetBounds: !0 }, i.prototype.clear = function() { this.data = [], this.maxValue = Number.NaN, this.minValue = Number.NaN }, i.prototype.resetBounds = function() { if (this.data.length) { this.maxValue = this.data[0][1], this.minValue = this.data[0][1]; for (var e = 1; e < this.data.length; e += 1) { var t = this.data[e][1];
                t > this.maxValue && (this.maxValue = t), t < this.minValue && (this.minValue = t) } } else this.maxValue = Number.NaN, this.minValue = Number.NaN }, i.prototype.append = function(e, t, i) { for (var a = this.data.length - 1; a >= 0 && this.data[a][0] > e;) a -= 1; - 1 === a ? this.data.splice(0, 0, [e, t]) : this.data.length > 0 && this.data[a][0] === e ? i ? (this.data[a][1] += t, t = this.data[a][1]) : this.data[a][1] = t : a < this.data.length - 1 ? this.data.splice(a + 1, 0, [e, t]) : this.data.push([e, t]), this.maxValue = isNaN(this.maxValue) ? t : Math.max(this.maxValue, t), this.minValue = isNaN(this.minValue) ? t : Math.min(this.minValue, t) }, i.prototype.dropOldData = function(e, t) { for (var i = 0; this.data.length - i >= t && this.data[i + 1][0] < e;) i += 1;
        0 !== i && this.data.splice(0, i) }, a.defaultChartOptions = { millisPerPixel: 20, enableDpiScaling: !0, yMinFormatter: function(e, t) { return parseFloat(e).toFixed(t) }, yMaxFormatter: function(e, t) { return parseFloat(e).toFixed(t) }, maxValueScale: 1, minValueScale: 1, interpolation: "bezier", scaleSmoothing: .125, maxDataSetLength: 2, scrollBackwards: !1, grid: { fillStyle: "#000000", strokeStyle: "#777777", lineWidth: 1, sharpLines: !1, millisPerLine: 1e3, verticalSections: 2, borderVisible: !0 }, labels: { fillStyle: "#ffffff", disabled: !1, fontSize: 10, fontFamily: "monospace", precision: 2 }, horizontalLines: [] }, a.AnimateCompatibility = { requestAnimationFrame: function(e, t) { return (window.requestAnimationFrame || window.webkitRequestAnimationFrame || window.mozRequestAnimationFrame || window.oRequestAnimationFrame || window.msRequestAnimationFrame || function(e) { return window.setTimeout(function() { e((new Date).getTime()) }, 16) }).call(window, e, t) }, cancelAnimationFrame: function(e) { return (window.cancelAnimationFrame || function(e) { clearTimeout(e) }).call(window, e) } }, a.defaultSeriesPresentationOptions = { lineWidth: 1, strokeStyle: "#ffffff" }, a.prototype.addTimeSeries = function(e, i) { this.seriesSet.push({ timeSeries: e, options: t.extend({}, a.defaultSeriesPresentationOptions, i) }), e.options.resetBounds && e.options.resetBoundsInterval > 0 && (e.resetBoundsTimerId = setInterval(function() { e.resetBounds() }, e.options.resetBoundsInterval)) }, a.prototype.removeTimeSeries = function(e) { for (var t = this.seriesSet.length, i = 0; i < t; i += 1)
            if (this.seriesSet[i].timeSeries === e) { this.seriesSet.splice(i, 1); break }
        e.resetBoundsTimerId && clearInterval(e.resetBoundsTimerId) }, a.prototype.getTimeSeriesOptions = function(e) { for (var t = this.seriesSet.length, i = 0; i < t; i += 1)
            if (this.seriesSet[i].timeSeries === e) return this.seriesSet[i].options }, a.prototype.bringToFront = function(e) { for (var t = this.seriesSet.length, i = 0; i < t; i += 1)
            if (this.seriesSet[i].timeSeries === e) { var a = this.seriesSet.splice(i, 1);
                this.seriesSet.push(a[0]); break } }, a.prototype.streamTo = function(e, t) { this.canvas = e, this.delay = t, this.start() }, a.prototype.resize = function() { if (this.options.enableDpiScaling && window && 1 !== window.devicePixelRatio) { var e = window.devicePixelRatio,
                t = parseInt(this.canvas.getAttribute("width")),
                i = parseInt(this.canvas.getAttribute("height"));
            this.originalWidth && Math.floor(this.originalWidth * e) === t || (this.originalWidth = t, this.canvas.setAttribute("width", Math.floor(t * e).toString()), this.canvas.style.width = t + "px", this.canvas.getContext("2d").scale(e, e)), this.originalHeight && Math.floor(this.originalHeight * e) === i || (this.originalHeight = i, this.canvas.setAttribute("height", Math.floor(i * e).toString()), this.canvas.style.height = i + "px", this.canvas.getContext("2d").scale(e, e)) } }, a.prototype.start = function() { if (!this.frame) { var e = function() { this.frame = a.AnimateCompatibility.requestAnimationFrame(function() { this.render(), e() }.bind(this)) }.bind(this);
            e() } }, a.prototype.stop = function() { this.frame && (a.AnimateCompatibility.cancelAnimationFrame(this.frame), delete this.frame) }, a.prototype.updateValueRange = function() { for (var e = this.options, t = Number.NaN, i = Number.NaN, a = 0; a < this.seriesSet.length; a += 1) { var s = this.seriesSet[a].timeSeries;
            isNaN(s.maxValue) || (t = isNaN(t) ? s.maxValue : Math.max(t, s.maxValue)), isNaN(s.minValue) || (i = isNaN(i) ? s.minValue : Math.min(i, s.minValue)) } if (null != e.maxValue ? t = e.maxValue : t *= e.maxValueScale, null != e.minValue ? i = e.minValue : i -= Math.abs(i * e.minValueScale - i), this.options.yRangeFunction) { var n = this.options.yRangeFunction({ min: i, max: t });
            i = n.min, t = n.max } if (!isNaN(t) && !isNaN(i)) { var r = t - i - this.currentValueRange,
                l = i - this.currentVisMinValue;
            this.isAnimatingScale = Math.abs(r) > .1 || Math.abs(l) > .1, this.currentValueRange += e.scaleSmoothing * r, this.currentVisMinValue += e.scaleSmoothing * l }
        this.valueRange = { min: i, max: t } }, a.prototype.render = function(e, t) { var i = (new Date).getTime(); if (!this.isAnimatingScale) { var a = Math.min(1e3 / 6, this.options.millisPerPixel); if (i - this.lastRenderTimeMillis < a) return }
        this.resize(), this.lastRenderTimeMillis = i, e = e || this.canvas, t = t || i - (this.delay || 0), t -= t % this.options.millisPerPixel; var s = e.getContext("2d"),
            n = this.options,
            r = { top: 0, left: 0, width: e.clientWidth, height: e.clientHeight },
            l = t - r.width * n.millisPerPixel,
            o = function(e) { var t = e - this.currentVisMinValue; return 0 === this.currentValueRange ? r.height : r.height - Math.round(t / this.currentValueRange * r.height) }.bind(this),
            h = function(e) { return n.scrollBackwards ? Math.round((t - e) / n.millisPerPixel) : Math.round(r.width - (t - e) / n.millisPerPixel) }; if (this.updateValueRange(), s.font = n.labels.fontSize + "px " + n.labels.fontFamily, s.save(), s.translate(r.left, r.top), s.beginPath(), s.rect(0, 0, r.width, r.height), s.clip(), s.save(), s.fillStyle = n.grid.fillStyle, s.clearRect(0, 0, r.width, r.height), s.fillRect(0, 0, r.width, r.height), s.restore(), s.save(), s.lineWidth = n.grid.lineWidth, s.strokeStyle = n.grid.strokeStyle, n.grid.millisPerLine > 0) { s.beginPath(); for (var d = t - t % n.grid.millisPerLine; d >= l; d -= n.grid.millisPerLine) { var u = h(d);
                n.grid.sharpLines && (u -= .5), s.moveTo(u, 0), s.lineTo(u, r.height) }
            s.stroke(), s.closePath() } for (var m = 1; m < n.grid.verticalSections; m += 1) { var c = Math.round(m * r.height / n.grid.verticalSections);
            n.grid.sharpLines && (c -= .5), s.beginPath(), s.moveTo(0, c), s.lineTo(r.width, c), s.stroke(), s.closePath() } if (n.grid.borderVisible && (s.beginPath(), s.strokeRect(0, 0, r.width, r.height), s.closePath()), s.restore(), n.horizontalLines && n.horizontalLines.length)
            for (var f = 0; f < n.horizontalLines.length; f += 1) { var g = n.horizontalLines[f],
                    p = Math.round(o(g.value)) - .5;
                s.strokeStyle = g.color || "#ffffff", s.lineWidth = g.lineWidth || 1, s.beginPath(), s.moveTo(0, p), s.lineTo(r.width, p), s.stroke(), s.closePath() }
        for (var S = 0; S < this.seriesSet.length; S += 1) { s.save(); var v = this.seriesSet[S].timeSeries,
                w = v.data,
                x = this.seriesSet[S].options;
            v.dropOldData(l, n.maxDataSetLength), s.lineWidth = x.lineWidth, s.strokeStyle = x.strokeStyle, s.beginPath(); for (var y = 0, b = 0, V = 0, T = 0; T < w.length && 1 !== w.length; T += 1) { var N = h(w[T][0]),
                    P = o(w[T][1]); if (0 === T) y = N, s.moveTo(N, P);
                else switch (n.interpolation) {
                    case "linear":
                    case "line":
                        s.lineTo(N, P); break;
                    case "bezier":
                    default:
                        s.bezierCurveTo(Math.round((b + N) / 2), V, Math.round(b + N) / 2, P, N, P); break;
                    case "step":
                        s.lineTo(N, V), s.lineTo(N, P) }
                b = N, V = P }
            w.length > 1 && (x.fillStyle && (s.lineTo(r.width + x.lineWidth + 1, V), s.lineTo(r.width + x.lineWidth + 1, r.height + x.lineWidth + 1), s.lineTo(y, r.height + x.lineWidth), s.fillStyle = x.fillStyle, s.fill()), x.strokeStyle && "none" !== x.strokeStyle && s.stroke(), s.closePath()), s.restore() } if (!n.labels.disabled && !isNaN(this.valueRange.min) && !isNaN(this.valueRange.max)) { var M = n.yMaxFormatter(this.valueRange.max, n.labels.precision),
                k = n.yMinFormatter(this.valueRange.min, n.labels.precision),
                F = n.scrollBackwards ? 0 : r.width - s.measureText(M).width - 2,
                R = n.scrollBackwards ? 0 : r.width - s.measureText(k).width - 2;
            s.fillStyle = n.labels.fillStyle, s.fillText(M, F, n.labels.fontSize), s.fillText(k, R, r.height - 2) } if (n.timestampFormatter && n.grid.millisPerLine > 0) { var A = n.scrollBackwards ? s.measureText(k).width : r.width - s.measureText(k).width + 4; for (d = t - t % n.grid.millisPerLine; d >= l; d -= n.grid.millisPerLine) { u = h(d); if (!n.scrollBackwards && u < A || n.scrollBackwards && u > A) { var B = new Date(d),
                        L = n.timestampFormatter(B),
                        W = s.measureText(L).width;
                    A = n.scrollBackwards ? u + W + 2 : u - W - 2, s.fillStyle = n.labels.fillStyle, n.scrollBackwards ? s.fillText(L, u, r.height - 2) : s.fillText(L, u - W, r.height - 2) } } }
        s.restore() }, a.timeFormatter = function(e) {
        function t(e) { return (e < 10 ? "0" : "") + e } return t(e.getHours()) + ":" + t(e.getMinutes()) + ":" + t(e.getSeconds()) }, e.TimeSeries = i, e.SmoothieChart = a }("undefined" == typeof exports ? this : exports);